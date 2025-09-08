#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// =============================================================================
// CONFIGURACIÓN POR CATEGORÍAS - Todas las palabras organizadas
// =============================================================================

// Directivas del preprocesador
typedef struct {
    const char *es;
    const char *c;
} PalabraDirectiva;

static const PalabraDirectiva DIRECTIVAS[] = {
    {"use", "#include"},
    {"def", "#define"},
    {"ifdef", "#ifdef"},
    {"ifndef", "#ifndef"},
    {"endif", "#endif"},
    {"ln", "#line"},
    {"meta", "#pragma"},
    {"fail", "#error"},
    {NULL, NULL}
};

// Tipos de datos
typedef struct {
    const char *es;
    const char *c;
} PalabraTipo;

static const PalabraTipo TIPOS[] = {
    {"num", "int"},
    {"chr", "char"},
    {"flt", "float"},
    {"dbl", "double"},
    {"lng", "long"},
    {"shrt", "short"},
    {"nil", "void"},
    {"sgn", "signed"},
    {"uns", "unsigned"},
    {NULL, NULL}
};

// Modificadores
typedef struct {
    const char *es;
    const char *c;
} PalabraModificador;

static const PalabraModificador MODIFICADORES[] = {
    {"stat", "static"},
    {"cons", "const"},
    {"ext", "extern"},
    {"reg", "register"},
    {"vol", "volatile"},
    {"alias", "typedef"},
    {"gen", "auto"},
    {"uniq", "restrict"},
    {"inl", "inline"},
    {NULL, NULL}
};

// Estructuras
typedef struct {
    const char *es;
    const char *c;
} PalabraEstructura;

static const PalabraEstructura ESTRUCTURAS[] = {
    {"rec", "struct"},
    {"un", "union"},
    {"list", "enum"},
    {NULL, NULL}
};

// Control de flujo
typedef struct {
    const char *es;
    const char *c;
} PalabraControl;

static const PalabraControl CONTROL_FLUJO[] = {
    {"if", "if"},
    {"els", "else"},
    {"loop", "while"},
    {"for", "for"},
    {"dop", "do"},
    {"case", "switch"},
    {"when", "case"},
    {"dfl", "default"},
    {"jmp", "goto"},
    {NULL, NULL}
};

// Saltos
typedef struct {
    const char *es;
    const char *c;
} PalabraSalto;

static const PalabraSalto SALTOS[] = {
    {"stop", "break"},
    {"next", "continue"},
    {"out", "return"},
    {NULL, NULL}
};

// Operadores especiales
typedef struct {
    const char *es;
    const char *c;
} PalabraOperador;

static const PalabraOperador OPERADORES[] = {
    {"size", "sizeof"},
    {"type", "typeof"},
    {NULL, NULL}
};

// Funciones de biblioteca
typedef struct {
    const char *es;
    const char *c;
} PalabraFuncion;

static const PalabraFuncion FUNCIONES[] = {
    {"start", "main"},
    {"print", "printf"},
    {"input", "scanf"},
    {"echo", "puts"},
    {"read", "gets"},
    {NULL, NULL}
};

// Signos de comentarios
typedef struct {
    const char *inicio;
    const char *fin;
    int es_linea;
} SignoComentario;

static const SignoComentario COMENTARIOS[] = {
    {"//", "\n", 1},  // Comentario de línea
    {"/*", "*/", 0},  // Comentario de bloque
    {NULL, NULL, 0}
};

// =============================================================================
// FUNCIONES DE BÚSQUEDA POR CATEGORÍAS
// =============================================================================

const char* buscar_en_directivas(const char *palabra) {
    for (int i = 0; DIRECTIVAS[i].es != NULL; i++) {
        if (strcmp(palabra, DIRECTIVAS[i].es) == 0) {
            return DIRECTIVAS[i].c;
        }
    }
    return NULL;
}

const char* buscar_en_tipos(const char *palabra) {
    for (int i = 0; TIPOS[i].es != NULL; i++) {
        if (strcmp(palabra, TIPOS[i].es) == 0) {
            return TIPOS[i].c;
        }
    }
    return NULL;
}

const char* buscar_en_modificadores(const char *palabra) {
    for (int i = 0; MODIFICADORES[i].es != NULL; i++) {
        if (strcmp(palabra, MODIFICADORES[i].es) == 0) {
            return MODIFICADORES[i].c;
        }
    }
    return NULL;
}

const char* buscar_en_estructuras(const char *palabra) {
    for (int i = 0; ESTRUCTURAS[i].es != NULL; i++) {
        if (strcmp(palabra, ESTRUCTURAS[i].es) == 0) {
            return ESTRUCTURAS[i].c;
        }
    }
    return NULL;
}

const char* buscar_en_control_flujo(const char *palabra) {
    for (int i = 0; CONTROL_FLUJO[i].es != NULL; i++) {
        if (strcmp(palabra, CONTROL_FLUJO[i].es) == 0) {
            return CONTROL_FLUJO[i].c;
        }
    }
    return NULL;
}

const char* buscar_en_saltos(const char *palabra) {
    for (int i = 0; SALTOS[i].es != NULL; i++) {
        if (strcmp(palabra, SALTOS[i].es) == 0) {
            return SALTOS[i].c;
        }
    }
    return NULL;
}

const char* buscar_en_operadores(const char *palabra) {
    for (int i = 0; OPERADORES[i].es != NULL; i++) {
        if (strcmp(palabra, OPERADORES[i].es) == 0) {
            return OPERADORES[i].c;
        }
    }
    return NULL;
}

const char* buscar_en_funciones(const char *palabra) {
    for (int i = 0; FUNCIONES[i].es != NULL; i++) {
        if (strcmp(palabra, FUNCIONES[i].es) == 0) {
            return FUNCIONES[i].c;
        }
    }
    return NULL;
}

// =============================================================================
// FUNCIONES DE VALIDACIÓN POR CATEGORÍAS
// =============================================================================

int es_directiva(const char *palabra) {
    return buscar_en_directivas(palabra) != NULL;
}

int es_tipo(const char *palabra) {
    return buscar_en_tipos(palabra) != NULL;
}

int es_modificador(const char *palabra) {
    return buscar_en_modificadores(palabra) != NULL;
}

int es_estructura(const char *palabra) {
    return buscar_en_estructuras(palabra) != NULL;
}

int es_control_flujo(const char *palabra) {
    return buscar_en_control_flujo(palabra) != NULL;
}

int es_salto(const char *palabra) {
    return buscar_en_saltos(palabra) != NULL;
}

int es_operador(const char *palabra) {
    return buscar_en_operadores(palabra) != NULL;
}

int es_funcion(const char *palabra) {
    return buscar_en_funciones(palabra) != NULL;
}

// =============================================================================
// FUNCIÓN PRINCIPAL DE TRADUCCIÓN
// =============================================================================

const char* traducir_palabra_por_categoria(const char *palabra) {
    const char *traduccion;

    if ((traduccion = buscar_en_directivas(palabra)) != NULL) return traduccion;
    if ((traduccion = buscar_en_tipos(palabra)) != NULL) return traduccion;
    if ((traduccion = buscar_en_modificadores(palabra)) != NULL) return traduccion;
    if ((traduccion = buscar_en_estructuras(palabra)) != NULL) return traduccion;
    if ((traduccion = buscar_en_control_flujo(palabra)) != NULL) return traduccion;
    if ((traduccion = buscar_en_saltos(palabra)) != NULL) return traduccion;
    if ((traduccion = buscar_en_operadores(palabra)) != NULL) return traduccion;
    if ((traduccion = buscar_en_funciones(palabra)) != NULL) return traduccion;

    return palabra; // No encontrada, devolver original
}

int es_palabra_reservada_general(const char *palabra) {
    return es_directiva(palabra) || es_tipo(palabra) || es_modificador(palabra) ||
    es_estructura(palabra) || es_control_flujo(palabra) || es_salto(palabra) ||
    es_operador(palabra) || es_funcion(palabra);
}

// =============================================================================
// MANEJO DE ERRORES POR CATEGORÍAS
// =============================================================================

void error_directiva_mal_usada(const char *palabra, int linea) {
    fprintf(stderr, "Error [línea %d]: La directiva '%s' no se puede usar como identificador\n",
            linea, palabra);
}

void error_tipo_mal_usado(const char *palabra, int linea) {
    fprintf(stderr, "Error [línea %d]: El tipo '%s' no se puede usar como variable\n",
            linea, palabra);
}

void error_modificador_mal_usado(const char *palabra, int linea) {
    fprintf(stderr, "Error [línea %d]: El modificador '%s' no se puede usar como identificador\n",
            linea, palabra);
}

void error_estructura_mal_usada(const char *palabra, int linea) {
    fprintf(stderr, "Error [línea %d]: La palabra '%s' está reservada para estructuras\n",
            linea, palabra);
}

void error_control_flujo_mal_usado(const char *palabra, int linea) {
    fprintf(stderr, "Error [línea %d]: La palabra de control '%s' no se puede usar como identificador\n",
            linea, palabra);
}

void error_salto_mal_usado(const char *palabra, int linea) {
    fprintf(stderr, "Error [línea %d]: La palabra de salto '%s' no se puede usar como identificador\n",
            linea, palabra);
}

void error_operador_mal_usado(const char *palabra, int linea) {
    fprintf(stderr, "Error [línea %d]: El operador '%s' no se puede usar como identificador\n",
            linea, palabra);
}

void error_funcion_mal_usada(const char *palabra, int linea) {
    fprintf(stderr, "Error [línea %d]: La función '%s' no se puede redefinir como variable\n",
            linea, palabra);
}

void error_comentario_no_cerrado(int linea) {
    fprintf(stderr, "Error [línea %d]: Comentario de bloque no cerrado\n", linea);
}

void error_string_no_cerrado(int linea) {
    fprintf(stderr, "Error [línea %d]: String no cerrado\n", linea);
}

void error_char_no_cerrado(int linea) {
    fprintf(stderr, "Error [línea %d]: Literal de carácter no cerrado\n", linea);
}

// =============================================================================
// VALIDACIÓN DE ERRORES POR CATEGORÍAS
// =============================================================================

void validar_error_por_categoria(const char *palabra, int linea, int siguiente_char) {
    int es_asignacion = (siguiente_char == '=');
    int es_llamada_funcion = (siguiente_char == '(');

    if (es_directiva(palabra) && (es_asignacion || es_llamada_funcion)) {
        error_directiva_mal_usada(palabra, linea);
    }
    else if (es_tipo(palabra) && es_asignacion) {
        error_tipo_mal_usado(palabra, linea);
    }
    else if (es_modificador(palabra) && (es_asignacion || es_llamada_funcion)) {
        error_modificador_mal_usado(palabra, linea);
    }
    else if (es_estructura(palabra) && es_asignacion) {
        error_estructura_mal_usada(palabra, linea);
    }
    else if (es_control_flujo(palabra) && es_asignacion) {
        error_control_flujo_mal_usado(palabra, linea);
    }
    else if (es_salto(palabra) && (es_asignacion || es_llamada_funcion)) {
        error_salto_mal_usado(palabra, linea);
    }
    else if (es_operador(palabra) && es_asignacion) {
        error_operador_mal_usado(palabra, linea);
    }
    else if (es_funcion(palabra) && es_asignacion) {
        error_funcion_mal_usada(palabra, linea);
    }
}

// =============================================================================
// FUNCIONES AUXILIARES PEQUEÑAS
// =============================================================================

int es_caracter_palabra(int c) {
    return isalnum(c) || c == '_';
}

int es_espacio_blanco(int c) {
    return c == ' ' || c == '\t' || c == '\n' || c == '\r';
}

int saltar_espacios_y_obtener_siguiente(FILE *archivo) {
    int c;
    do {
        c = fgetc(archivo);
    } while (es_espacio_blanco(c) && c != EOF);

    if (c != EOF) {
        ungetc(c, archivo);
    }
    return c;
}

// =============================================================================
// ESTRUCTURAS Y CONSTANTES
// =============================================================================

typedef enum {
    ESTADO_NORMAL = 0,
    ESTADO_COMENTARIO_LINEA,
    ESTADO_COMENTARIO_BLOQUE,
    ESTADO_STRING,
    ESTADO_CHAR
} Estado;

#define MAX_PALABRA 256

typedef struct {
    FILE *entrada;
    FILE *salida;
    int linea_actual;
    int tiene_errores;
    Estado estado;
    char buffer_palabra[MAX_PALABRA];
    int pos_palabra;
} Transpilador;

// =============================================================================
// FUNCIONES DE ESCRITURA
// =============================================================================

void escribir_caracter(Transpilador *trans, int c) {
    fputc(c, trans->salida);
    if (c == '\n') {
        trans->linea_actual++;
    }
}

void escribir_cadena(Transpilador *trans, const char *str) {
    while (*str) {
        escribir_caracter(trans, *str++);
    }
}

// =============================================================================
// FUNCIONES DE MANEJO DE PALABRAS
// =============================================================================

void agregar_a_palabra(Transpilador *trans, int c) {
    if (trans->pos_palabra < MAX_PALABRA - 1) {
        trans->buffer_palabra[trans->pos_palabra++] = c;
    }
}

void limpiar_buffer_palabra(Transpilador *trans) {
    trans->pos_palabra = 0;
    memset(trans->buffer_palabra, 0, MAX_PALABRA);
}

void procesar_palabra_completa(Transpilador *trans) {
    if (trans->pos_palabra == 0) {
        return;
    }

    trans->buffer_palabra[trans->pos_palabra] = '\0';

    if (es_palabra_reservada_general(trans->buffer_palabra)) {
        int siguiente = saltar_espacios_y_obtener_siguiente(trans->entrada);
        if (siguiente != EOF) {
            validar_error_por_categoria(trans->buffer_palabra,
                                        trans->linea_actual, siguiente);
            if (siguiente == '=' || siguiente == '(') {
                trans->tiene_errores = 1;
            }
        }
    }

    escribir_cadena(trans, traducir_palabra_por_categoria(trans->buffer_palabra));
    limpiar_buffer_palabra(trans);
}

// =============================================================================
// FUNCIONES DE MANEJO DE COMENTARIOS
// =============================================================================

int detectar_inicio_comentario_linea(Transpilador *trans, int c) {
    if (c != '/') return 0;

    int siguiente = fgetc(trans->entrada);
    if (siguiente == '/') {
        escribir_cadena(trans, "//");
        trans->estado = ESTADO_COMENTARIO_LINEA;
        return 1;
    }

    if (siguiente != EOF) {
        ungetc(siguiente, trans->entrada);
    }
    return 0;
}

int detectar_inicio_comentario_bloque(Transpilador *trans, int c) {
    if (c != '/') return 0;

    int siguiente = fgetc(trans->entrada);
    if (siguiente == '*') {
        escribir_cadena(trans, "/*");
        trans->estado = ESTADO_COMENTARIO_BLOQUE;
        return 1;
    }

    if (siguiente != EOF) {
        ungetc(siguiente, trans->entrada);
    }
    return 0;
}

void procesar_fin_comentario_bloque(Transpilador *trans, int c) {
    escribir_caracter(trans, c);

    if (c == '*') {
        int siguiente = fgetc(trans->entrada);
        if (siguiente == '/') {
            escribir_caracter(trans, siguiente);
            trans->estado = ESTADO_NORMAL;
        } else if (siguiente != EOF) {
            ungetc(siguiente, trans->entrada);
        }
    }
}

// =============================================================================
// FUNCIONES DE MANEJO DE STRINGS Y CHARS
// =============================================================================

void procesar_escape_en_literal(Transpilador *trans) {
    int escapado = fgetc(trans->entrada);
    if (escapado != EOF) {
        escribir_caracter(trans, escapado);
    }
}

void iniciar_string(Transpilador *trans, int c) {
    procesar_palabra_completa(trans);
    escribir_caracter(trans, c);
    trans->estado = ESTADO_STRING;
}

void iniciar_char(Transpilador *trans, int c) {
    procesar_palabra_completa(trans);
    escribir_caracter(trans, c);
    trans->estado = ESTADO_CHAR;
}

// =============================================================================
// FUNCIÓN PRINCIPAL DE PROCESAMIENTO DE CARACTERES
// =============================================================================

void procesar_caracter_normal(Transpilador *trans, int c) {
    if (detectar_inicio_comentario_linea(trans, c) ||
        detectar_inicio_comentario_bloque(trans, c)) {
        procesar_palabra_completa(trans);
        } else if (c == '"') {
            iniciar_string(trans, c);
        } else if (c == '\'') {
            iniciar_char(trans, c);
        } else if (es_caracter_palabra(c)) {
            agregar_a_palabra(trans, c);
        } else {
            procesar_palabra_completa(trans);
            escribir_caracter(trans, c);
        }
}

void procesar_caracter(Transpilador *trans, int c) {
    switch (trans->estado) {
        case ESTADO_NORMAL:
            procesar_caracter_normal(trans, c);
            break;

        case ESTADO_COMENTARIO_LINEA:
            escribir_caracter(trans, c);
            if (c == '\n') {
                trans->estado = ESTADO_NORMAL;
            }
            break;

        case ESTADO_COMENTARIO_BLOQUE:
            procesar_fin_comentario_bloque(trans, c);
            break;

        case ESTADO_STRING:
            escribir_caracter(trans, c);
            if (c == '\\') {
                procesar_escape_en_literal(trans);
            } else if (c == '"') {
                trans->estado = ESTADO_NORMAL;
            }
            break;

        case ESTADO_CHAR:
            escribir_caracter(trans, c);
            if (c == '\\') {
                procesar_escape_en_literal(trans);
            } else if (c == '\'') {
                trans->estado = ESTADO_NORMAL;
            }
            break;
    }
}

// =============================================================================
// FUNCIONES DE INICIALIZACIÓN Y ARCHIVOS
// =============================================================================

void inicializar_transpilador(Transpilador *trans, FILE *entrada, FILE *salida) {
    trans->entrada = entrada;
    trans->salida = salida;
    trans->linea_actual = 1;
    trans->tiene_errores = 0;
    trans->estado = ESTADO_NORMAL;
    limpiar_buffer_palabra(trans);
}

int abrir_archivos(const char *archivo_entrada, const char *archivo_salida,
                   FILE **entrada, FILE **salida) {
    *entrada = fopen(archivo_entrada, "r");
    if (!*entrada) {
        perror("Error al abrir archivo de entrada");
        return 0;
    }

    *salida = fopen(archivo_salida, "w");
    if (!*salida) {
        perror("Error al abrir archivo de salida");
        fclose(*entrada);
        return 0;
    }

    return 1;
                   }

                   void cerrar_archivos(FILE *entrada, FILE *salida) {
                       if (entrada) fclose(entrada);
                       if (salida) fclose(salida);
                   }

                   void mostrar_uso() {
                       printf("Uso: transpilador <entrada.es> <salida.c>\n");
                       printf("Transpila código de español a C\n");
                   }

                   void mostrar_resultado(int tiene_errores, const char *entrada, const char *salida) {
                       if (tiene_errores) {
                           printf("Transpilación completada con errores. Revisa los mensajes.\n");
                       } else {
                           printf("Transpilación exitosa: %s -> %s\n", entrada, salida);
                       }
                   }

                   // =============================================================================
                   // FUNCIÓN PRINCIPAL
                   // =============================================================================

                   int main(int argc, char *argv[]) {
                       if (argc < 3) {
                           mostrar_uso();
                           return 1;
                       }

                       FILE *entrada, *salida;
                       if (!abrir_archivos(argv[1], argv[2], &entrada, &salida)) {
                           return 1;
                       }

                       Transpilador trans;
                       inicializar_transpilador(&trans, entrada, salida);

                       int c;
                       while ((c = fgetc(entrada)) != EOF) {
                           procesar_caracter(&trans, c);
                       }

                       procesar_palabra_completa(&trans);
                       cerrar_archivos(entrada, salida);

                       mostrar_resultado(trans.tiene_errores, argv[1], argv[2]);
                       return trans.tiene_errores ? 1 : 0;
                   }
