// 0x441ef0: x87 polar-vector setter.
    struct AnimationLeafPolarVector {                                                          
        float x;                                                           
        float y;                                                           
        __attribute__((thiscall, noinline)) AnimationLeafPolarVector* SetAnimationPolar(float angle, float radius); 
    };                                                                     
    AnimationLeafPolarVector* AnimationLeafPolarVector::SetAnimationPolar(float angle, float radius) {                          
        AnimationLeafPolarVector* volatile storedReceiver = this;                              
        AnimationLeafPolarVector* destination = storedReceiver;                                
        volatile float& radians = angle;                                   
        long double sine, cosine;                                          
        __builtin_sincosl(static_cast<long double>(radians), &sine, &cosine); 
        volatile float& scale = radius;                                    
        destination->x = static_cast<float>(cosine * static_cast<long double>(scale)); 
        destination->y = static_cast<float>(sine * static_cast<long double>(scale)); 
        return destination;                                                
    }
