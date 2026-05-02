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

inline Value make_int(int value)     { 
    Value val; 
    val.type = TYPE_INT; 
    val.int_value = value; 
    return val;
}
inline Value make_float(float value) { Value val; val.type = TYPE_FLOAT; val.float_value = value; return val;}
inline Value make_char(char value)   { Value val; val.type = TYPE_CHAR; val.char_value = value; return val;}
inline Value make_bool(int value)    { Value val; val.type = TYPE_BOOL; val.bool_value = value; return val;}

inline Value to_float(Value v) {
    return make_float((v.type == TYPE_INT) ? (float)v.int_value : v.float_value);
}

inline int is_true(Value v) {
    if (v.type == TYPE_BOOL) return v.bool_value;
    if (v.type == TYPE_INT) return v.int_value != 0;
    if (v.type == TYPE_FLOAT) return v.float_value != 0.0f;
    if (v.type == TYPE_CHAR) return v.char_value != 0;
    return 0;
}

// Op aritméticas

inline Value add(Value a, Value b) {
    if(a.type == TYPE_FLOAT || b.type == TYPE_FLOAT) {
        float fa = a.type == TYPE_INT ? (float)a.int_value : a.float_value;
        float fb = b.type == TYPE_INT ? (float)b.int_value : b.float_value;
        return make_float(fa + fb);
    }
    return make_int(a.int_value + b.int_value);
}

inline Value sub(Value a, Value b) {
    if(a.type == TYPE_FLOAT || b.type == TYPE_FLOAT) {
        float fa = a.type == TYPE_INT ? (float)a.int_value : a.float_value;
        float fb = b.type == TYPE_INT ? (float)b.int_value : b.float_value;
        return make_float(fa - fb);
    }
    return make_int(a.int_value - b.int_value);
}

inline Value mul(Value a, Value b) {
    if(a.type == TYPE_FLOAT || b.type == TYPE_FLOAT) {
        float fa = a.type == TYPE_INT ? (float)a.int_value : a.float_value;
        float fb = b.type == TYPE_INT ? (float)b.int_value : b.float_value;
        return make_float(fa * fb);
    }
    return make_int(a.int_value * b.int_value);
}

inline Value divv(Value a, Value b) {
    if(a.type == TYPE_FLOAT || b.type == TYPE_FLOAT) {
        float fa = a.type == TYPE_INT ? (float)a.int_value : a.float_value;
        float fb = b.type == TYPE_INT ? (float)b.int_value : b.float_value;
        return make_float(fa / fb);
    }
    return make_int(a.int_value / b.int_value);
}

inline Value mod(Value a, Value b) {
    int ia = a.type == TYPE_FLOAT ? (int)a.float_value : a.int_value;
    int ib = b.type == TYPE_FLOAT ? (int)b.float_value : b.int_value;
    return make_int(ia % ib);
}

// Op relacionais
inline Value equal(Value a, Value b){
    if(a.type == TYPE_FLOAT || b.type == TYPE_FLOAT) {
        float fa = a.type == TYPE_INT ? (float)a.int_value : a.float_value;
        float fb = b.type == TYPE_INT ? (float)b.int_value : b.float_value;
        return make_bool(fa == fb);
    }
    if(a.type == TYPE_INT)  return make_bool(a.int_value == b.int_value);
    if(a.type == TYPE_BOOL) return make_bool(a.bool_value == b.bool_value);
    if(a.type == TYPE_CHAR) return make_bool(a.char_value == b.char_value);
    return make_bool(0);
}

inline Value nequal(Value a, Value b){
    Value val = equal(a, b);
    return make_bool(!val.bool_value);
}

inline Value less(Value a, Value b) {
    if(a.type == TYPE_FLOAT || b.type == TYPE_FLOAT) {
        float fa = a.type == TYPE_INT ? (float)a.int_value : a.float_value;
        float fb = b.type == TYPE_INT ? (float)b.int_value : b.float_value;
        return make_bool(fa < fb);
    }
    return make_bool(a.int_value < b.int_value);
}

inline Value great(Value a, Value b) {
    if(a.type == TYPE_FLOAT || b.type == TYPE_FLOAT) {
        float fa = a.type == TYPE_INT ? (float)a.int_value : a.float_value;
        float fb = b.type == TYPE_INT ? (float)b.int_value : b.float_value;
        return make_bool(fa > fb);
    }
    return make_bool(a.int_value > b.int_value);
}

inline Value lequal(Value a, Value b) {
    if(a.type == TYPE_FLOAT || b.type == TYPE_FLOAT) {
        float fa = a.type == TYPE_INT ? (float)a.int_value : a.float_value;
        float fb = b.type == TYPE_INT ? (float)b.int_value : b.float_value;
        return make_bool(fa <= fb);
    }
    return make_bool(a.int_value <= b.int_value);
}

inline Value gequal(Value a, Value b) {
    if(a.type == TYPE_FLOAT || b.type == TYPE_FLOAT) {
        float fa = a.type == TYPE_INT ? (float)a.int_value : a.float_value;
        float fb = b.type == TYPE_INT ? (float)b.int_value : b.float_value;
        return make_bool(fa >= fb);
    }
    return make_bool(a.int_value >= b.int_value);
}

// Op lógicas
inline Value op_or(Value a, Value b) {
    return make_bool(is_true(a) || is_true(b));
}

inline Value op_and(Value a, Value b) {
    return make_bool(is_true(a) && is_true(b));
}

inline Value op_not(Value a) {
    return make_bool(!is_true(a));
}

#endif // RUNTIME_H