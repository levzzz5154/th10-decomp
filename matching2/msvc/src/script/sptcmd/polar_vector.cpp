// 0x4501b0: x87 polar-vector setter.
    struct EclPolarVector {                                                          
        float x;                                                           
        float y;                                                           
        __attribute__((thiscall, noinline)) EclPolarVector* SetPolar(float angle, float radius); 
    };                                                                     
    EclPolarVector* EclPolarVector::SetPolar(float angle, float radius) {                          
        EclPolarVector* volatile storedReceiver = this;                              
        EclPolarVector* destination = storedReceiver;                                
        volatile float& radians = angle;                                   
        long double sine, cosine;                                          
        __builtin_sincosl(static_cast<long double>(radians), &sine, &cosine); 
        volatile float& scale = radius;                                    
        destination->x = static_cast<float>(cosine * static_cast<long double>(scale)); 
        destination->y = static_cast<float>(sine * static_cast<long double>(scale)); 
        return destination;                                                
    }
