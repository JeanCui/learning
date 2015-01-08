//
//  trigger.h
//  c++_trigger_class
//
//  Created by JinCui on 1/7/15.
//  Copyright (c) 2015 JinCui. All rights reserved.
//


#ifndef c___trigger_class_trigger_h
#define c___trigger_class_trigger_h

#include <string>
#include <map>

template<typename TReturn, typename TParameter, typename TDefaultKey = std::string>
class Trigger {
public:
    typedef boost::function<TReturn (TParameter)> triggerFunction_T;
    typedef std::map<TDefaultKey, triggerFunction_T> triggerMap_T;
    typedef std::pair<TDefaultKey, triggerFunction_T> triggerPair_T;
    
    Trigger(){
        triggers.reset(new triggerMap_T);
    }
    
    virtual ~Trigger(){
        
    }
    
    /** Register a class member trigger function.
     *
     */
    template<typename TFunction, typename TObject>
    int addTriggerAcceptor(TDefaultKey name, TFunction f, TObject obj){
        typename triggerMap_T::iterator it;
        triggerFunction_T                    trigger = boost::bind(f,obj,_1);
        it = triggers->find(name);
        
        triggers->insert(triggerPair_T(name, f));
        return 0;
    }
    
    int addTriggerAcceptor(TDefaultKey name, triggerFunction_T f)
    {
        typename triggerMap_T::iterator it;
        
        it = triggers->find(name);
        triggers->insert(triggerPair_T(name, f));
        return 0;
    }
    
    TReturn raiseTrigger(TDefaultKey name, TParameter param){
        typename triggerMap_T::iterator it;
        
        it = triggers->find(name);
        if (it != triggers->end()) {
            return it->second(param);
        }
    }
    
private:
    boost::shared_ptr<triggerMap_T> triggers;
    
};


#endif
