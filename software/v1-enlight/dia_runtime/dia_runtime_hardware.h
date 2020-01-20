#ifndef dia_runtime_hardware_h
#define dia_runtime_hardware_h

#include "dia_functions.h"

extern "C" {
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}

#include "LuaBridge.h"
#include <string>
#include <jansson.h>
#include <list>

using namespace luabridge;

class DiaRuntimeHardware {
public:
    std::string Name;

    void * light_object;
    int (*turn_light_function)(void * object, int pin, int animation_id);
    int TurnLight(int light_pin, int AnimationID) {
        //printf("light pin:[%d]->animation:[%d];\n", light_pin, AnimationID);
        if(light_object && turn_light_function) {
            turn_light_function(light_object, light_pin, AnimationID);
        } else {
            //printf("error: NIL object or function TurnLight\n");
        }
        return 0;
    }

    void * program_object;
    int (*turn_program_function)(void * object, int program);
    int TurnProgram(int ProgramNum) {
        if(program_object && turn_program_function) {
            turn_program_function(program_object, ProgramNum);
        } else {
            //printf("error: NIL object or function TurnActivator\n");
        }
        return 0;
    }

    int (*send_receipt_function)(int postPosition, int isCard, int amount);
    int SendReceipt(int postPosition, int isCard, int amount) {
	if(send_receipt_function) {
	    send_receipt_function(postPosition, isCard, amount);
	} else {
	    printf("error: NIL function SendReceipt\n");
	}
	return 0;
    }

    void * coin_object;
    int (*get_coins_function)(void * object);
    int GetCoins() {
        //printf("get coins;\n");
        if(coin_object && get_coins_function) {
            return get_coins_function(coin_object);
        } else {
            printf("error: NIL object or function GetCoins\n");
        }
        return 0;
    }

    void * banknote_object;
    int (*get_banknotes_function)(void * object);
    int GetBanknotes() {
        //printf("get banknotes;\n");
        if(banknote_object && get_banknotes_function) {
            return get_banknotes_function(banknote_object);
        } else {
            printf("error: NIL object or function GetBanknotes\n");
        }
        return 0;
    }

    void * keys_object;
    int (*get_keys_function)(void * object);
    
    int GetKey() {
        #ifndef USE_GPIO
        assert(get_keys_function);
        return get_keys_function(0);
        #endif
        if(keys_object && get_keys_function) {
            return get_keys_function(keys_object);
        }
        printf("error: NIL object or function GetKey\n");
        return 0;
    }

    void * delay_object;
    int (*smart_delay_function)(void * object, int milliseconds);
    int SmartDelay(int milliseconds) {
        if(delay_object && smart_delay_function) {
            return smart_delay_function(delay_object, milliseconds);
        } else {
            printf("error: NIL object or function SmartDelay\n");
        }
        return 0;
    }

    DiaRuntimeHardware() {
        light_object = 0;
        turn_light_function = 0;

        program_object = 0;
        turn_program_function = 0;

	send_receipt_function = 0;

        coin_object = 0;
        get_coins_function = 0;

        banknote_object = 0;
        get_banknotes_function = 0;

        keys_object = 0;
        get_keys_function = 0;

        delay_object = 0;
        smart_delay_function = 0;
    }
};

#endif
