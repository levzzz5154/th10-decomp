#include "th10/game/enemy_projectile_spawn.hpp"
#include <algorithm>
#include <cmath>
namespace th10::enemy_projectile {
namespace { constexpr float kTau=6.2831853071795864769f; }
// Semantic reconstruction of retail 0x004067D0. IDA's __userpurge
// declaration confirms the descriptor in EBX and the pool/column/row/angle
// stack arguments used by caller 0x004073E0.
bool EnemyProjectile_SpawnOne(SpawnPool& pool,const SpawnDescriptor& d,unsigned column,int row,float base,const SpawnEdges&e){
    if(pool.slots.empty()) return false;
    const std::size_t limit=std::min<std::size_t>(2000,pool.slots.size()); std::size_t found=limit;
    for(std::size_t n=0;n<limit;++n){std::size_t i=(pool.cursor+n)%limit;if(!pool.slots[i].active){found=i;break;}}
    if(found==limit)return false;
    float speed=d.rows<2?d.speed0:d.speed0-(d.speed0-d.speed1)*float(row)/float(d.rows);
    float angle=0.0f;
    switch(d.layout){
      case 0: case 1: angle=(d.parity_flags&1)?float((column+1)/2):float(column/2)+.5f; angle*=d.spacing;if(column&1)angle=-angle;if(d.layout==0)angle+=base;angle+=d.z;break;
      case 2: angle=base; [[fallthrough]]; case 3: angle+=float(row)*d.spacing+float(column)*kTau/float(std::max<unsigned>(1,d.columns))+d.z;break;
      case 4: angle=base; [[fallthrough]]; case 5: angle+=float(row)*d.spacing+(float(column)+.5f)*kTau/float(std::max<unsigned>(1,d.columns))+d.z;break;
      case 6: angle=d.spacing+(e.random_symmetric?e.random_symmetric(e.random_context,d.spacing):0.0f);break;
      case 7: speed=d.speed1+(e.random_symmetric?e.random_symmetric(e.random_context,d.speed1):0.0f);angle=float(row)*d.spacing+float(column)*kTau/float(std::max<unsigned>(1,d.columns))+d.z;break;
      case 8: angle=d.spacing+(e.random_symmetric?e.random_symmetric(e.random_context,d.spacing):0.0f);speed=d.speed1+(e.random_symmetric?e.random_symmetric(e.random_context,d.speed1):0.0f);break;
      default: break;
    }
    SpawnSlot&s=pool.slots[found]; s={};s.active=true;s.state=1;s.type=d.type;s.variant=d.variant;s.x=d.x;s.y=d.y;s.z=.1f;s.angle=std::remainder(angle,kTau);s.speed=speed;s.flags=d.flags;s.payload=d.payload;s.payload_tag=d.payload_tag;s.payload_value=d.payload_value;
    s.state=(d.flags&2)?7:(d.flags&4)?8:(d.flags&8)?9:2;
    if(e.initialize_motion) e.initialize_motion(s);
    if(e.publish) e.publish(s);
    pool.cursor=(found+1)%limit;return true;
}

} // namespace th10::enemy_projectile
