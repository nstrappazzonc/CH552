# Fundamentos de lenguaje C51

## Estructura básica

Todo programa empieza en una función `main` de la siguiente forma:

```c
void main(void) {
	// sentencias ...
}
```

## Manipulación de bit (bitwise)

### OR

El Operador OR es utilizado para la asignación un bit. Se representa con el símbolo `|`.

| A | B | A\|B |
|---|---|:---:|
| 1 | 0 |  0  |
| 1 | 1 |  1  |
| 0 | 0 |  0  |
| 0 | 1 |  1  |

Por ejemplo: `0b00001010 | 0b00000001 = 0b00001011`.

### AND

El operador AND es utilizado para deshacer la asignación un bit. Se representa con el símbolo `&`.

| A | B | A&B |
|---|---|:---:|
| 1 | 0 |  0  |
| 1 | 1 |  1  |
| 0 | 0 |  0  |
| 0 | 1 |  0  |

Por ejemplo: `0bxxxxxxxx & 0x10000000 = 0b1xxxxxxx`.

### XOR

El operador XOR (OR exclusivo) es utilizado para hacer la inversión (flipping) un bit. Se representa con el símbolo `^`.

| A | B | A^B |
|---|---|:---:|
| 1 | 0 |  1  |
| 1 | 1 |  0  |
| 0 | 0 |  0  |
| 0 | 1 |  1  |

### Shifting



### NOT



### Consideraciones

#### Asignación con operadores

La siguiente forma de hacer la asignacion con operadores son validas:

```
P30 = P30 | 0b00000001;
P30 |= 0b00000001;
```

#### Componer operadores

La siguiente forma de componer varias asignaciones con operadores son validas:

```
PORTB |= (1 << PINB0)|(1 << PINB2)|(1 << PINB4);
PORTB &= ~((1 << PINB0)|(1 << PINB2)|(1 << PINB4));
```

## Sentencia de control

### IF

### Switch

```c
switch(variable){
    case 0:
    	// sentencias ...
      break;
    case 1:
    	// sentencias ...
      break;
    // case n:
    //   sentencias ...
    default:
    	// sentencias ...
}
```
