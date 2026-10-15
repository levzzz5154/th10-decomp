// 0x41beb0: x87 polar-vector setter.
    struct ScoreItemPolarVector {                                                          
        float x;                                                           
        float y;                                                           
        __attribute__((thiscall, noinline)) ScoreItemPolarVector* SetItemPolar(float angle, float radius); 
    };                                                                     
    ScoreItemPolarVector* ScoreItemPolarVector::SetItemPolar(float angle, float radius) {                          
        ScoreItemPolarVector* volatile storedReceiver = this;                              
        ScoreItemPolarVector* destination = storedReceiver;                                
        volatile float& radians = angle;                                   
        long double sine, cosine;                                          
        __builtin_sincosl(static_cast<long double>(radians), &sine, &cosine); 
        volatile float& scale = radius;                                    
        destination->x = static_cast<float>(cosine * static_cast<long double>(scale)); 
        destination->y = static_cast<float>(sine * static_cast<long double>(scale)); 
        return destination;                                                
    }
