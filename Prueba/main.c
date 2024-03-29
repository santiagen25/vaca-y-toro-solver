#include <stdio.h>
#include <stdbool.h>

//para compiliar y crear un ejecutable en ubuntu, gcc -o main main.c

int err(int type);

int main(int argc, char *argv[])
{
	//generamos la base de datos como array
	int bd[3024];
	int next_n = 0;
	for(int c = 1234; c < 9999; c++) {
		int v_a[4];
		int val_val = c;
		for(int d = 0; d<4; d++) {
			v_a[d] = val_val % 10;
			val_val /= 10;
		}
		if(v_a[0]!=0 && v_a[1]!=0 && v_a[2]!=0 && v_a[3]!=0) {
			if (v_a[0] != v_a[1] && v_a[0] != v_a[2] && v_a[0] != v_a[3] && v_a[1] != v_a[2] && v_a[1] != v_a[3] && v_a[2] != v_a[3]) {
				//el numero tiene digitos sin repetir y sin ceros, guardamos en la bd
				bd[next_n++] = c;
			}
		}
	}

	int numero = 1234, vacas = 0, toros = 0, numeros_disponibles = 3024, intentos = 1, siguiente;

 	while(true){

		//Desmembramos el numero NUMERO que hay que decir
		int value_n = numero, nums_n[4];
		bool para_siguiente = true;

		for(int k = 0; k < 4; k++){
			nums_n[k] = value_n % 10;
			value_n /= 10;
		}

		printf("Di el numero: %d\n", numero);
		bool numeroDeVoT = false, sumaDeVyT = false;
		do{
			printf("\nCuantas VACAS hay?\n");
			scanf("%d", &vacas);
			numeroDeVoT = vacas > 4 || vacas < 0;
			if (numeroDeVoT) err(1);
		} while (numeroDeVoT);
		
		do{
			printf("Cuantos TOROS hay?\n");
			scanf("%d", &toros);
			numeroDeVoT = toros > 4 || toros < 0;
			sumaDeVyT = (vacas + toros) > 4;
			if (numeroDeVoT) err(2);
			else if (sumaDeVyT) err(3);
		} while (numeroDeVoT || sumaDeVyT);
		


		for(int n = 0; n < 3024; n++){
			if(bd[n] != 0){

				//Desmembramos el numero N dado
				int value = bd[n], nums[4];

				for(int k = 0; k < 4; k++){
					nums[k] = value % 10;
					value /= 10;
				}

				//Empezamos a comparar y descartar numeros
				int encajes = 0, coincidencias = 0;

				for(int l = 0; l < 4; l++){
					for(int m = 0; m < 4; m++){
						if(nums_n[l] == nums[m]){
							if(l == m) encajes++;
							else coincidencias++;
							break;
						}
					}
				}

				if(numeros_disponibles <= 1){
					if(bd[n] == 0) printf("La informaci�n recibida de vacas y toros no es correcta, no hay ning�n numero con esas especificaciones.");
					else printf("El numero que queda es el: %d\nNumero de intentos realizados: %d\n", bd[n], intentos);
					int a;
					scanf("%d", &a);
					return 0;
				}

				//con los resultados de vaca-toro de este nuevo numero comparamos con los dados anteriormente
				if(coincidencias != vacas || encajes != toros){
					bd[n] = 0;
					numeros_disponibles--;
				} else if(para_siguiente){
					siguiente = n;
					para_siguiente = false;
				}
				if(bd[n] != 0) printf("%d\n",bd[n]);
			}
		}
		if (numeros_disponibles == 1) printf("El numero que pensabas es el %d", numeros_disponibles);
		else if(numeros_disponibles =< 0) err(4);

		printf("Numeros disponibles: %d\tPorcentaje de numeros que quedan: %.2f\tNumero de intentos %d\n", numeros_disponibles, ((float)numeros_disponibles*100/3024), intentos);
		intentos++;

		//miramos cual es el siguiente numero que se ha de decir
		numero = bd[siguiente];
	}
}

int err (int type) {
	printf("\nERROR: ");
	if(type == 1) printf("Las VACAS han de ser de 0 a 5");
	else if(type == 2) printf("Los TOROS han de ser de 0 a 5");
	else if(type == 3) printf("La suma de TOROS y VACAS no puede ser mayor de 4");
	else if(type == 4) printf("Algo ha ido mal, ningún número encaja con tus directrices");
	else if(type == 5) printf("n/a");
	else printf("Not defined");
	printf("\n");

	return 0;
}
