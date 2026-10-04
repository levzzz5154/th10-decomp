from pathlib import Path
import json,re,subprocess,sys
from matching2.tools.common.wine import DEFAULT_TOOLKIT,compiler_environment,winpath
from matching2.tools.matching.ltcg_cluster import _absolute_object
from matching2.tools.common.coff_regions import _read_object
p=Path('matching2/reference/semantic_candidates/ending_screen_0042d300').resolve()
variant=sys.argv[1] if len(sys.argv)>1 else 'opaque'
source={'opaque':'title_dispatcher.cpp','leaves':'native_leaves.cpp','music':'music_caller.cpp','adapter':'adapter_context.cpp','adapter_public_music':'adapter_context.cpp','full_script':'full_script_context.cpp','full_script_count':'full_script_count.cpp','full_script_menu':'full_script_menu.cpp','full_script_menu_history':'full_script_menu.cpp','full_script_menu_push':'full_script_menu_push.cpp','full_script_menu_leaves':'full_script_menu_leaves.cpp','full_script_menu_member':'full_script_menu_member.cpp','full_script_menu_no_global':'full_script_menu_no_global.cpp','full_script_menu_cursor':'full_script_menu_cursor.cpp','full_script_menu_clamp':'full_script_menu_clamp.cpp','full_script_menu_direct_exit':'full_script_menu_direct_exit.cpp'}[variant]
w=Path('matching2/build/experiments/ending_screen_caller_'+variant+'_2026_10_04').resolve();w.mkdir(parents=True,exist_ok=True)
env=compiler_environment(DEFAULT_TOOLKIT);cmds=[]
sources=[p/source]
if variant in ('music','adapter','adapter_public_music'):sources.append(Path('matching2/msvc/src/game/recovery_install_animation_slot_0042c670.cpp').resolve())
if variant.startswith('full_script'):
 spec=json.loads(Path('matching2/msvc/layout/ltcg/recovery_animation_slot_frames_0042c6d0.json').read_text())
 sources += [(Path('matching2/msvc')/item).resolve() for item in spec['additional_sources']]
if variant in ('full_script_menu_leaves','full_script_menu_member','full_script_menu_no_global','full_script_menu_cursor','full_script_menu_clamp','full_script_menu_direct_exit'):
 sources += [(Path('matching2/msvc')/item).resolve() for item in ('src/game/progress.cpp','src/render/animation_manager_set_stop_frame_and_run_00449250.cpp','src/game/game_state_dispatch_animation_slot_secondary_0042c750.cpp','src/render/animation_manager_find_004491c0.cpp')]
objects={}
for mode in ('ordinary','gl'):
 objects[mode]=[]
 for index,input_path in enumerate(sources):
  object_path=w/(mode+('' if index==0 else '_'+str(index))+'.obj')
  objects[mode].append(object_path)
  cmd=['wine',str(DEFAULT_TOOLKIT/'bin/cl.exe'),'/nologo','/c','/O2','/Gz','/MT','/Gy','/G6','/GF','/GS','/Zl']
  if mode=='gl':cmd+=['/GL']
  cmd+=['/I'+winpath(Path('matching2/msvc/include').resolve()),'/Fo'+winpath(object_path),winpath(input_path)]
  r=subprocess.run(cmd,env=env,capture_output=True,text=True);(w/(mode+'_'+str(index)+'.log')).write_text(r.stdout+r.stderr);cmds.append(cmd);assert r.returncode==0,r.stdout+r.stderr
records=[record for object_path in objects['ordinary'] for record in _read_object(object_path)['records']]
defined={item['name'] for item in records if item.get('section_number',0)>0 and item.get('storage_class')==2}
bindings=[]
known={}
production_config=json.loads(Path('matching2/msvc/regions.json').read_text())
production_symbols=production_config['symbols']
for region in production_config['regions']:
 if region.get('kind') in ('semantic','asm','library'):
  known[region['symbol']]=(int(str(region['address']),0),'relative_code')
for layout in Path('matching2/msvc/layout/ltcg').glob('*.json'):
 spec=json.loads(layout.read_text())
 for group in ('functions','anchors','externals','absolute_symbols','constant_aliases','data_aliases'):
  for entry in spec.get(group,[]):
   if isinstance(entry,dict) and 'symbol' in entry and 'address' in entry:
    known[entry['symbol']]=(int(str(entry['address']),0),entry.get('kind','data' if group in ('constant_aliases','data_aliases') else 'relative_code'))

method={'?Find@RecoveryLookup_0040bd80':0x4491c0,'?SetTimerTarget@':0x42c620,'?DisableTimerWithOwner@':0x42c5c0,'?SetSlotFrame@':0x42c770,'?Queue@':0x43dc90,'?MarkResourceForRemoval@':0x4493e0}
other={'_data_004749ce':0x4749ce,'_free':0x4524a1,'__ftol2':0x463b2c,'__fltused':0}
seen=set()
for item in records:
 if item.get('section_number')!=0 or item.get('storage_class')!=2:continue
 name=item['name']
 if name in defined or name in seen:continue
 seen.add(name)
 address=None;kind='relative_code'
 if name.startswith('_data_'):address=int(name[6:],16);kind='data'
 else:
  match=re.search(r'_([0-9a-f]{8})(?:@@|@|$)',name)
  address=int(match[1],16) if match else other.get(name)
  for prefix,value in method.items():
   if name.startswith(prefix):address=value
 if name=='__fltused':kind='data'
 if name in known:address,kind=known[name]
 if address is None and name in production_symbols:
  address=int(str(production_symbols[name]),0);kind='relative_code' if item.get('type',0)&0x20 and not name.startswith('__imp_') else 'data'
 if address is None:raise ValueError(name)
 bindings.append({'symbol':name,'kind':kind,'coff_value':address-0x400000 if kind=='relative_code' else address})
_absolute_object(w/'bindings.obj',bindings)
root='RecoveryAnimationSlotFramesCompilerContext@20' if variant.startswith('full_script') else 'RecoveryMusicRoom_Update_00433ef0@4' if variant=='adapter_public_music' else '?Update@TitleRuntime@@QAEHXZ' if variant=='adapter' else '?TitleDispatcher_Update_0042cdf0@@YGHPAURecoveryMusicRoom_00433ef0@@@Z'
cmd=['wine',str(DEFAULT_TOOLKIT/'bin/link.exe'),'/nologo','/LTCG','/NODEFAULTLIB','/MACHINE:X86','/SUBSYSTEM:CONSOLE','/BASE:0x400000','/FIXED','/OPT:REF','/OPT:NOICF','/ENTRY:'+root,'/OUT:'+winpath(w/'native.exe'),'/MAP:'+winpath(w/'native.map'),*[winpath(obj) for obj in objects['gl']],winpath(w/'bindings.obj')]
if variant in ('adapter_public_music','full_script','full_script_count','full_script_menu','full_script_menu_history','full_script_menu_push','full_script_menu_leaves','full_script_menu_member','full_script_menu_no_global','full_script_menu_cursor','full_script_menu_clamp','full_script_menu_direct_exit'):cmd.insert(2,'/INCLUDE:?Update@TitleRuntime@@QAEHXZ')
r=subprocess.run(cmd,env=env,capture_output=True,text=True);(w/'link.log').write_text(r.stdout+r.stderr);cmds.append(cmd);print(r.returncode,r.stdout+r.stderr)
(w/'commands.json').write_text(json.dumps(cmds,indent=2))
print(w)
