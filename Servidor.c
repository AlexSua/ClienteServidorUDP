
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <ctype.h>

int main() {
    int Socket;
    int puerto,puertoRem,n,i;
    printf("Introduce puerto propio: ");
    scanf("%d",&puerto);
    char mensajeRecibido[1000];
    struct sockaddr_in dirPropia;
    struct sockaddr_in dirRemota;
    socklen_t tDireccion;
    dirPropia.sin_addr.s_addr=htonl(INADDR_ANY);
    dirPropia.sin_family=AF_INET;
    dirPropia.sin_port=htons(puerto);
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
        tDireccion=sizeof(dirRemota);
        while(1){
        if ((n=recvfrom (Socket,mensajeRecibido,1000,0,&dirRemota,&tDireccion))==-1){
            perror("No se pudo recibir el mensaje");
            exit(-1);
        }
        printf("\nMensaje recibido de [Direccion %s y puerto %d] de %d bytes\n",inet_ntoa(dirRemota.sin_addr),ntohs(dirRemota.sin_port),n);
        printf("\n-------->%s\n\n",mensajeRecibido);
        printf("Pasando a mayusculas y enviando....\n");
        for(i=0;i<strlen(mensajeRecibido);i++){
            mensajeRecibido[i]=toupper(mensajeRecibido[i]);
        }
        mensajeRecibido[strlen(mensajeRecibido)]='\0';
        if ((n=sendto (Socket,(void*)mensajeRecibido,sizeof(mensajeRecibido),0,&dirRemota, tDireccion))==-1){
            perror("No se pudo enviar el mensaje");
        }
        }
        close(Socket);
    
    } 
    return (EXIT_SUCCESS);
}