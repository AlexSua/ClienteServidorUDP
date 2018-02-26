
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

int main() {
    int Socket;
    int puerto,puertoRem,n;
    printf("Introduce puerto propio: ");
    scanf("%d",&puerto);
    printf("Introduce puerto remoto: ");
    scanf("%d",&puertoRem);
    char mensaje[1000];
    struct sockaddr_in dirPropia;
    struct sockaddr_in dirRemota;
    socklen_t tDireccion;
    dirPropia.sin_addr.s_addr=htonl(INADDR_ANY);
    dirPropia.sin_family=AF_INET;
    dirPropia.sin_port=htons(puerto);
    dirRemota.sin_addr.s_addr=inet_addr("127.0.0.1");
    dirRemota.sin_family=AF_INET;
    dirRemota.sin_port=htons(puertoRem);
    Socket=socket(PF_INET,SOCK_DGRAM,0);
    if (Socket<0){
        perror("No se pudo crear socket");
        exit(-1);
    }
    else{
        tDireccion=sizeof(dirPropia);
        if (bind (Socket,(struct sockaddr *)&dirPropia,tDireccion)<0){
            perror("No se pudo asignar direccion");
            exit(-1);
        }
        while(1){
        printf("Introduce el mensaje a pasar a mayusculas: ");
        scanf(" %[^\n]",mensaje);
        tDireccion=sizeof(dirRemota);
        if ((n=sendto (Socket,(void*)mensaje,sizeof(mensaje),0,&dirRemota, tDireccion))==-1){
            perror("No se pudo enviar el mensaje");
        }
        printf("\nMensaje enviado de [%d] bytes\n",n);
        if ((n=recvfrom (Socket,mensaje,1000,0,&dirRemota,&tDireccion))==-1){
            perror("No se pudo recibir el mensaje");
            exit(-1);
        }
        printf("\nEl mensaje pasado a mayusculas es:\n------>%s\n",mensaje);
        }
        close(Socket);
    } 
    return (EXIT_SUCCESS);
}

