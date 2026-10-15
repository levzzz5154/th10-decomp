// 0x41f800: x87 polar-vector setter.
    struct PathPolarVector {                                                          
        float x;                                                           
        float y;                                                           
        __attribute__((thiscall, noinline)) PathPolarVector* SetPathPolar(float angle, float radius); 
    };                                                                     
    PathPolarVector* PathPolarVector::SetPathPolar(float angle, float radius) {                          
        PathPolarVector* volatile storedReceiver = this;                              
        PathPolarVector* destination = storedReceiver;                                
        volatile float& radians = angle;                                   
        long double sine, cosine;                                          
        __builtin_sincosl(static_cast<long double>(radians), &sine, &cosine); 
        volatile float& scale = radius;                                    
        destination->x = static_cast<float>(cosine * static_cast<long double>(scale)); 
        destination->y = static_cast<float>(sine * static_cast<long double>(scale)); 
        return destination;                                                
    }
