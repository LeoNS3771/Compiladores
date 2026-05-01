#ifndef RUNTIME_H
#define RUNTIME_H


typedef enum {TYPE_INT, TYPE_FLOAT, TYPE_CHAR, TYPE_BOOL} valueType;

typedef struct {
    valueType type;
    union {
        int int_value;
        float float_value;
        char char_value;
        int bool_value;
    };
} Value;

//
Value make_int(int value)   { Value val; val.type = TYPE_INT; val.int_value = value; return val;}
Value make_float(float value) { Value val; val.type = TYPE_FLOAT; val.float_value = value; return val;}
Value make_char(char value)  { Value val; val.type = TYPE_CHAR; val.char_value = value; return val;}
Value make_bool(bool value)  { Value val; val.type = TYPE_BOOL; val.bool_value = value; return val;}


Value to_float(Value v) return (v.type == TYPE_INT) ? (float)v.int_value : v.float_value;

// Deve ter como simplificar isso aqui
Value add(Value a, Value b) {
    if(a.type == TYPE_FLOAT || b.type == TYPE_FLOAT) {
        float fa = a.type == TYPE_INT ? (float)a.int_val : a.float_val;
        float fb = b.type == TYPE_INT ? (float)b.int_val : b.float_val;
        return make_float(fa + fb);
    }
    return make_int(a.int_val + b.int_val);
}

Value sub(Value a, Value b) {
    if(a.type == TYPE_FLOAT || b.type == TYPE_FLOAT) {
        float fa = a.type == TYPE_INT ? (float)a.int_val : a.float_val;
        float fb = b.type == TYPE_INT ? (float)b.int_val : b.float_val;
        return make_float(fa - fb);
    }
    return make_int(a.int_val - b.int_val);
}

Value mul(Value a, Value b) {
    if(a.type == TYPE_FLOAT || b.type == TYPE_FLOAT) {
        float fa = a.type == TYPE_INT ? (float)a.int_val : a.float_val;
        float fb = b.type == TYPE_INT ? (float)b.int_val : b.float_val;
        return make_float(fa * fb);
    }
    return make_int(a.int_val * b.int_val);
}

Value div(Value a, Value b){
    if(a.type == TYPE_FLOAT || b.type == TYPE_FLOAT) {
        float fa = a.type == TYPE_INT ? (float)a.int_val : a.float_val;
        float fb = b.type == TYPE_INT ? (float)b.int_val : b.float_val;
        return make_float(fa / fb);
    }
    return make_int(a.int_val / b.int_val);
}

Value div(Value a, Value b){
    if(a.type == TYPE_FLOAT || b.type == TYPE_FLOAT) {
        float fa = a.type == TYPE_INT ? (float)a.int_val : a.float_val;
        float fb = b.type == TYPE_INT ? (float)b.int_val : b.float_val;
        return make_float(fa / fb);
    }
    return make_int(a.int_val / b.int_val);
}


Value equal(Value a, Value b){
    if(a.type == TYPE_FLOAT || b.type == TYPE_FLOAT)
        float fa = a.type == TYPE_INT ? (float)a.int_val : a.float_val;
        float fb = b.type == TYPE_INT ? (float)b.int_val : b.float_val;
        return make_bool(fa == fb);

    if(a.type == TYPE_INT)
        return make_bool(a.int_value == b.int_value);

    if(a.type == TYPE_BOOL)
        return make_bool(a.bool_value == b.bool_value);

    if(a.type == TYPE_CHAR)
        return make_bool(a.char_value == b.char_value);

    return make_bool(0);
}

Value nequal(Value a, Value b){
    bool val = equal(a, b);
    int res = val.char_value;
    if(char_value) return make_bool(1);
    return make_bool(0);
}

#endif // DEBUG