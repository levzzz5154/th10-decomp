// 0x44c5d0: x87 polar-vector setter.
    struct RecoveryPolarVector {                                                          
        float x;                                                           
        float y;                                                           
        __attribute__((thiscall, noinline)) RecoveryPolarVector* SetPolar(float angle, float radius); 
    };                                                                     
    RecoveryPolarVector* RecoveryPolarVector::SetPolar(float angle, float radius) {                          
        RecoveryPolarVector* volatile storedReceiver = this;                              
        RecoveryPolarVector* destination = storedReceiver;                                
        volatile float& radians = angle;                                   
        long double sine, cosine;                                          
        __builtin_sincosl(static_cast<long double>(radians), &sine, &cosine); 
        volatile float& scale = radius;                                    
        destination->x = static_cast<float>(cosine * static_cast<long double>(scale)); 
        destination->y = static_cast<float>(sine * static_cast<long double>(scale)); 
        return destination;                                                
    }
