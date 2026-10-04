from pathlib import Path
import subprocess,json,re,sys,os
sys.path.insert(0,str(Path.cwd()))
from matching2.tools.common.wine import DEFAULT_TOOLKIT,compiler_environment,winpath
w=Path('matching2/build/experiments/ending_screen_caller_full_script_menu_clamp_2026_10_04').resolve();out=w/'allocator_symbols';out.mkdir(exist_ok=True)
command=json.loads((w/'commands.json').read_text())[-1]
args=[str(DEFAULT_TOOLKIT/'bin/link.exe'),*[('/OUT:'+winpath(out/'native.exe') if a.startswith('/OUT:') else '/MAP:'+winpath(out/'native.map') if a.startswith('/MAP:') else a) for a in command[2:]]]
env=compiler_environment(DEFAULT_TOOLKIT)
p=subprocess.Popen(['winedbg','--gdb','--no-start',*args],stdout=subprocess.PIPE,stderr=subprocess.STDOUT,text=True,env=env)
port=None;lines=[]
for line in p.stdout:
 lines.append(line)
 match=re.search(r'target remote localhost:(\d+)',line)
 if match:port=match[1];break
if not port:raise RuntimeError('No debugger port: '+''.join(lines))
print('Live linker debugger port',port,flush=True)
script='''import gdb
from pathlib import Path
gdb.execute('set pagination off')
gdb.execute('set confirm off')
gdb.execute('target remote localhost:PORT')
out=open('OUTPUT','w')
def u32(address):return int(gdb.parse_and_eval('*(unsigned int*)%d'%address))
def names(sym):
    import re
    pending=[(sym,0)];seen=set();found=[]
    while pending and len(seen)<16:
        address,depth=pending.pop(0)
        if address in seen:continue
        seen.add(address)
        try:raw=gdb.selected_inferior().read_memory(address,256).tobytes()
        except Exception:continue
        for match in re.finditer(rb'[A-Za-z_?][A-Za-z0-9_?$@.]{2,95}\\x00',raw):
            found.append('%x+%x:%s'%(address,match.start(),match[0][:-1].decode()))
        if depth<2:
            for offset in (0,0x30,0x34,0x38,0x3c):
                value=int.from_bytes(raw[offset:offset+4],'little')
                if 0x10000<value<0x10000000 and value not in seen:pending.append((value,depth+1))
    return ' '.join(found)
gdb.execute('hbreak *0x107A98EE')
gdb.execute('hbreak *0x107AAC16')
for event in range(3000):
    try:gdb.execute('continue')
    except gdb.error:break
    try:
        pc=int(gdb.parse_and_eval('$pc'));esp=int(gdb.parse_and_eval('$esp'))
        if pc==0x107A98EE:
            out.write('GROUP K=%d w=%d\\n'%(int(gdb.parse_and_eval('$eax')),u32(esp+0x24)))
            for reg in ('ebx','esi'):
                item=int(gdb.parse_and_eval('$'+reg))&0xffffffff
                for count in range(64):
                    if not item:break
                    sym=u32(item);priority=u32(item+0xc);priority=priority if priority<0x80000000 else priority-(1<<32)
                    out.write('LIST %s id=%d symbol=%x priority=%d reg=%d %s\\n'%(reg,u32(item+0x1c),sym,priority,u32(item+0x18),'')))
                    item=u32(item+0x14)
        elif pc==0x107AAC16:
            item=u32(esp+0x20);sym=u32(item);priority=u32(item+0xc);priority=priority if priority<0x80000000 else priority-(1<<32)
            out.write('CHOOSE id=%d symbol=%x priority=%d register=%d %s\\n'%(u32(item+0x1c),sym,priority,u32(esp+0x10),names(sym)))
        else:out.write('OTHER stop=0x%x\\n'%pc)
        out.flush()
    except Exception as error:
        out.write('READ_ERROR '+str(error)+'\\n');out.flush()
out.close()
try:gdb.execute('detach')
except gdb.error:pass
'''.replace('PORT',port).replace('OUTPUT',str(out/'allocation.txt'))
(out/'trace.gdb.py').write_text(script)
try:
 r=subprocess.run(['gdb','-q','-batch','-x',str(out/'trace.gdb.py')],capture_output=True,text=True,timeout=180)
 (out/'gdb.log').write_text(r.stdout+r.stderr)
 print('gdb exit',r.returncode,flush=True)
 p.wait(timeout=30)
except Exception as error:
 print(type(error).__name__,str(error),flush=True)
 p.terminate()
finally:
 (out/'winedbg.log').write_text(''.join(lines))
print('Trace lines',len((out/'allocation.txt').read_text().splitlines()) if (out/'allocation.txt').exists() else 0,flush=True)
