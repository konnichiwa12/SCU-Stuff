//Lab6 Client

/* * Name: Dillon Kanai 
* Date: 2/9/2021
* Title: Lab6 Client
* Description: Send a file to a server using Stop and Wait and Timeout and receive ACKs*/

#include "lab6.h"

//getChecksum()
int getChecksum(Packet packet) {
    packet.header.cksum = 0;
    int checksum = 0;
    char *ptr = (char *)&packet;
    char *end = ptr + sizeof(Header) + packet.header.len;
    while (ptr < end) {
        checksum ^= *ptr++;
    } 
        return checksum;
}

void printPacket(Packet packet) {
    printf("Packet{ header: { seq_ack: %d, len: %d, cksum: %d }, data: \"",
            packet.header.seq_ack,
            packet.header.len,
            packet.header.cksum);
    fwrite(packet.data, (size_t)packet.header.len, 1, stdout);
    printf("\" }\n");
}

void ClientSend(int sockfd, const struct sockaddr *address, socklen_t addrlen, Packet packet, unsigned retries) {
    while (1) {
        //if retries is greater than 3, we give up and move on
	    if(retries>=3){
		    break;
	    }
        // calculate the checksum
        //******STUDENT WORK******
        packet.header.cksum = getChecksum(packet);
        
        // Print what is being sent
        printf("Created: ");
        printPacket(packet);

        // Simulate lost packet.
        if (rand() % PLOSTMSG == 0) {
            printf("Dropping packet\n");
        } else {
            //******STUDENT WORK******
            sendto(sockfd, &packet, sizeof(packet), 0, address, addrlen);
        }

        // wait until an ACK is received or timeout using select statement
        // recall recvfrom() is a blocking function, i.e. blocks until data is available
        // so what if data from server got lost, so select() solves this problem. type man select for more information.

        struct timeval tv;
        tv.tv_sec = 1;
        tv.tv_usec = 0;
        int rv;
        //setup select parameters
        fd_set readfds;
        fcntl(sockfd,F_SETFL,O_NONBLOCK);
        //start before calling select
        FD_ZERO(&readfds);
        FD_SET(sockfd,&readfds);
        //call select. sockfd+1 is used because select checks upto sockfd-1 descriptors.
        rv=select(sockfd+1,&readfds,NULL,NULL,&tv);
        if(rv==0){ // no data has been received
            printf("Timeout\n");
            //increment retries if packet is dropped
            retries++;
        }
        else{ //if rv!=0, there is something to receive
            //******STUDENT WORK******
                
        
            // receive an ACK from the server
            Packet recvpacket;
            //******STUDENT WORK******
            int count = recvfrom(sockfd, &recvpacket, sizeof(recvpacket), 0, (struct sockaddr*)&address, &addrlen);
            // print what was received
            printf("Received ACK %d, checksum %d - ", recvpacket.header.seq_ack, recvpacket.header.cksum);

            // validate the ACK
            if (recvpacket.header.cksum != getChecksum(recvpacket)) {
                // bad checksum, resend packet
                printf("Bad checksum, expected %d\n", getChecksum(recvpacket));
            } else if (packet.header.seq_ack != recvpacket.header.seq_ack) {
                // incorrect sequence number, resend packet
                printf("Bad seqnum, expected %d\n", packet.header.seq_ack);
            } else {
                // good ACK, we're done
                printf("Good ACK\n");
                break;
            }
        }
    }
    printf(" \n");
}

int main(int argc, char *argv[]) {
    // check arguments
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <ip> <port> <infile>\n", argv[0]);
        return 1;
    }

    // seed the RNG
    srand((unsigned)time(NULL));

    // create and configure the socket
    //******STUDENT WORK******
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    // initialize the server address structure
    //******STUDENT WORK******
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr(argv[1]);
    address.sin_port = htons(atoi(argv[2]));
    socklen_t addrlen = sizeof(address);

    // open file
    FILE *file = fopen(argv[3], "r");
    if (file == NULL) {
        perror("fopen");
        return 1;
    }

    // send file contents to server
    Packet packet;
    //******STUDENT WORK******
    int items = 0, seqnum = 0;
    Packet pack;
    while(items = fread(pack.data, 1, sizeof(pack.data), file)){
        pack.header.seq_ack = seqnum;
        pack.header.len = items;
        pack.header.cksum = getChecksum(pack);
        ClientSend(sockfd, (struct sockaddr*)&address, addrlen, pack, seqnum);
        seqnum = (seqnum + 1) % 2;
    }
    

    // send zero-length packet to server to end connection according the description provided in the Lab manual
    //******STUDENT WORK******
    Packet zero;
    zero.header.seq_ack = seqnum;
    zero.header.cksum = getChecksum(zero);
    zero.header.len = 0;
	ClientSend(sockfd, (struct sockaddr*)&address, addrlen, zero, 0);

    // clean up
    //******STUDENT WORK******
    fclose(file);
    close(sockfd);    
    return 0;
}
