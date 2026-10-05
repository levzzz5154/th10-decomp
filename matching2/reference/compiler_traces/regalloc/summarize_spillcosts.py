import sys,re
blocks=[];cur=None
for l in open(sys.argv[1]):
    if l.startswith('BLOCK'):
        m=re.match(r'BLOCK K=(\d+) weight=(\d+)',l);cur=dict(K=int(m[1]),w=int(m[2]),c=[]);blocks.append(cur)
    else:
        m=re.match(r'\s+(\w+) c=(\w+) num=(\d+) refs=(-?\d+) prio=(-?\d+) flags=(\w+) sym=(\w+) \{(\w+) (\w+)',l)
        if m: cur['c'].append(dict(l=m[1],c=m[2],num=int(m[3]),refs=int(m[4]),prio=int(m[5]),fl=m[6],sym=m[7],s1=m[9]))
funcs=[];f=None
for b in blocks:
    if all(c['prio']==0 for c in b['c']) and (f is None or any(c['prio'] for bb in f for c in bb['c'])): f=[];funcs.append(f)
    f.append(b)
sel=int(sys.argv[2]) if len(sys.argv)>2 else None
for i,f in enumerate(funcs):
    nums={}
    for b in f:
        for c in b['c']: nums[c['num']]=(c['prio'],c['fl'],c['s1'])
    if sel is None: print(i,'blocks',len(f),'cands',{k:v[0] for k,v in sorted(nums.items())},'imm',[k for k,v in nums.items() if v[2].endswith('100d')])
    elif sel==i:
        for b in f:
            print('K=%d w=%d'%(b['K'],b['w']),' '.join('%s#%d%s r%d p%d'%(c['l'][1],c['num'],'i' if c['s1'].endswith('100d') else '',c['refs'],c['prio']) for c in b['c']))
