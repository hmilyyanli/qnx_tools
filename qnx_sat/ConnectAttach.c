/* 
 * Message Client Process 
 */ 

#include <stdio.h> 
#include <unistd.h> 
#include <stdlib.h> 
#include <fcntl.h> 
#include <errno.h> 
#include <string.h> 
#include <sys/neutrino.h> 
#include <sys/iofunc.h> 
#include <sys/dispatch.h>
#include <sys/time.h>

typedef struct 
{ 
    uint16_t msg_no; 
    char msg_data[100*1024*1024]; 
} client_msg_t; 

client_msg_t msg;

int main( int argc, char **argv ) 
{  
    int  coid;
    char rmsg [256];
    pid_t pid;
    int chid;
    struct timeval tv;
    pid = strtol( argv[1], 0, 0 );
    chid = strtol( argv[2], 0, 0 );
	// establish a connection
    printf("connect to 0/%d/%d\n", pid, chid);

    coid = ConnectAttach (0, pid, chid, 0, 0);
    if (coid == -1) {
        fprintf (stderr, "Couldn't ConnectAttach to 0/77/1!\n");
        perror (NULL);
        exit (EXIT_FAILURE);
    }
    memset(&msg,0,sizeof(msg));
    sprintf(msg.msg_data,"Hello");
    gettimeofday(&tv, NULL);
    printf("start time %ld,%ld\n",tv.tv_sec,tv.tv_usec);
    // send the message
    if (MsgSend (coid,
                 (void*)&msg, 
                 sizeof (msg), 
                 rmsg, 
                 sizeof (rmsg)) == -1) {
        fprintf (stderr, "Error during MsgSend\n");
        perror (NULL);
        exit (EXIT_FAILURE);
    }
    //printf("end time %ld\n",time(NULL));
    gettimeofday(&tv, NULL);
    printf("end time %ld,%ld\n",tv.tv_sec,tv.tv_usec);
    if (strlen (rmsg) > 0) {
        printf ("Process ID %d returns \"%s\"\n", pid,rmsg);
    }
    ConnectDetach(coid);
#if 0	
    int fd; 
    int c; 
    //client_msg_t msg; 
    long ret; 
    int num; 
    char msg_reply[255]; 
    
    num = 1; 
    
    /* Process any command line arguments */ 
    while( ( c = getopt( argc, argv, "n:" ) ) != -1 ) 
    { 
        if( c == 'n' ) 
        { 
            num = strtol( optarg, 0, 0 ); 
        } 
    } 
    /* Open a connection to the server (fd == coid) */ 
    fd = open( "serv", O_RDWR ); 
    if( fd == -1 ) 
    { 
        fprintf( stderr, "Unable to open server connection: %s\n", 
            strerror( errno ) ); 
        return EXIT_FAILURE; 
    } 
    
    /* Clear the memory for the msg and the reply */ 
    memset( &msg, 0, sizeof( msg ) ); 
    memset( &msg_reply, 0, sizeof( msg_reply ) ); 
    
    /* Set up the message data to send to the server */ 
    msg.msg_no = _IO_MAX + num; 
    snprintf( msg.msg_data, 254, "client send %d\n.", sizeof(msg) ); 
    
    printf( "client: msg_no: _IO_MAX + %d\n", num ); 
    fflush( stdout ); 
 	
    /* record the time */
    printf("start time %ld\n",time(NULL));   
    /* Send the data to the server and get a reply */ 
    ret = MsgSend( fd, &msg, sizeof( msg ), msg_reply, 255 ); 
    if( ret == -1 ) 
    { 
        fprintf( stderr, "Unable to MsgSend() to server: %s\n", strerror( errno ) ); 
        return EXIT_FAILURE; 
    }
    printf("end time %ld\n",time(NULL));   
    /* Print out the reply data */ 
    printf( "client: server replied: %s\n", msg_reply ); 
    
    close( fd ); 
    
    return EXIT_SUCCESS; 
#endif

}
