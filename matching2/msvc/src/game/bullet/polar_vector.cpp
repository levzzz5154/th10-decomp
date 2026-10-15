// 0x408750: x87 polar-vector setter.
    struct ScoreGameplayPolarVector {                                                          
        float x;                                                           
        float y;                                                           
        __attribute__((thiscall, noinline)) ScoreGameplayPolarVector* SetScorePolar(float angle, float radius); 
    };                                                                     
    ScoreGameplayPolarVector* ScoreGameplayPolarVector::SetScorePolar(float angle, float radius) {                          
        ScoreGameplayPolarVector* volatile storedReceiver = this;                              
        ScoreGameplayPolarVector* destination = storedReceiver;                                
        volatile float& radians = angle;                                   
        long double sine, cosine;                                          
        __builtin_sincosl(static_cast<long double>(radians), &sine, &cosine); 
        volatile float& scale = radius;                                    
        destination->x = static_cast<float>(cosine * static_cast<long double>(scale)); 
        destination->y = static_cast<float>(sine * static_cast<long double>(scale)); 
        return destination;                                                
    }
