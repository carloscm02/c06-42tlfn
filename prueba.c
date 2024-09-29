#include <unistd.h>

int inicializar(int lgth){
    int solution;
    int i;
    
    solution = 0;
    i = 0;
    while (i < lgth)
    {
        solution = solution*10 + i;
        i++;
    }
    return solution;
}

void pintar(int number, int lgth){
    int max_decimal = 1;
    int char_real_decimal;

    while (lgth > 1)
    {
        max_decimal *= 10;
        lgth--;
    }

    while (max_decimal)
    {
        char_real_decimal = (number / max_decimal) % 10 + '0';
        write(1, &char_real_decimal, 4);
        max_decimal /= 10;
    }
}

int get_left_number(int number, int lgth){
    int i;
    int cent; //10, 100, 1000...

    i = 1;
    cent = 1;
    while (i < lgth)
    {
        cent *= 10;
        i++;
    }
    return number / cent;    
}

int sumar_decimal(int number, int current_position){
    int real_number = number + current_position;
    int base_number; //numero inmediatamente anterior
    current_position = current_position / 10;

    while (current_position)
    {
        int numero_a_quitar = (real_number / current_position) % 10;
        base_number = (real_number / (current_position * 10)) % 10;
        real_number = real_number - numero_a_quitar*current_position + (base_number + 1) * current_position;
        current_position /= 10;
    }
    return real_number;    
}

int current_position_cent(int cent){
    int cero_number = 0;

    while (cent >= 10)
    {
        cent /= 10;
        cero_number++;
    }
    return cero_number;
}

void principal(int nb){
    int number;

    number = inicializar(nb);

    int current_position = 1;

    while(get_left_number(number, nb)  + nb -1 < 9){
        int position_value = (number / current_position) % 10;//3
        int invert_position = current_position_cent(current_position);//0
        if(position_value + invert_position == 9){
            current_position *= 10;
        }else{
            pintar(number, nb);
            write(1, ", ",2);
            number = sumar_decimal(number, current_position);
            current_position = 1;
        }
    }
    pintar(number, nb);
}

int main()
{
    principal(5);
    return 0;
}
