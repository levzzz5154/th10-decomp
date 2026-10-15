// 0x4458b0: x87 polar-vector setter.
    struct AnimationPolarVector {                                                          
        float x;                                                           
        float y;                                                           
        __attribute__((thiscall, noinline)) AnimationPolarVector* SetAnimationPolar(float angle, float radius); 
    };                                                                     
    AnimationPolarVector* AnimationPolarVector::SetAnimationPolar(float angle, float radius) {                          
        AnimationPolarVector* volatile storedReceiver = this;                              
        AnimationPolarVector* destination = storedReceiver;                                
        volatile float& radians = angle;                                   
        long double sine, cosine;                                          
        __builtin_sincosl(static_cast<long double>(radians), &sine, &cosine); 
        volatile float& scale = radius;                                    
        destination->x = static_cast<float>(cosine * static_cast<long double>(scale)); 
        destination->y = static_cast<float>(sine * static_cast<long double>(scale)); 
        return destination;                                                
    }
