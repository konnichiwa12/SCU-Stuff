//Lab6 Server

/* * Name: Dillon Kanai 
* Date: 2/9/2021
* Title: Lab6 Server
* Description: Receive a file from a client using Stop and Wait and Timeout and send ACKs*/

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

//print packet
void printPacket(Packet packet) {
    printf("Packet{ header: { seq_ack: %d, len: %d, cksum: %d }, data: \"",
            packet.header.seq_ack,
            packet.header.len,
            packet.header.cksum);
    fwrite(packet.data, (size_t)packet.header.len, 1, stdout);
    printf("\" }\n");
}

//serverSend()
void serverSend(int sockfd, const struct sockaddr *address, socklen_t addrlen, int seqnum) {
    // Simulating a chance that ACK gets lost
    if (rand() % PLOSTMSG == 0) {
        printf("Dropping ACK\n");
    }
    else{
        Packet packet;
        //prepare and send the ACK
        //******STUDENT WORK******
        packet.header.len = sizeof(packet.data);
        packet.header.seq_ack = seqnum;
        packet.header.cksum = getChecksum(packet);
        if (sendto(sockfd, &packet, sizeof(packet), 0, address, addrlen) < 0){
            perror("file failed to send\n");
	        exit(1);
        }
        printf("Sent ACK %d, checksum %d\n", packet.header.seq_ack, packet.header.cksum);
    }
}

Packet serverReceive(int sockfd, struct sockaddr *address, socklen_t *addr_len, int seqnum)
{
                     
    Packet packet;

    while (1) {
        //Receive a packet from the client
        //******STUDENT WORK******
        int bytes = recvfrom(sockfd, &packet, sizeof(packet), 0, address, addr_len);

        // validate the length of the packet
        //******STUDENT WORK******
    

        // print what was received
        printf("Received: ");
        printPacket(packet);

        //verify the checksum and the sequence number
        if (packet.header.cksum != getChecksum(packet)) {
            printf("Bad checksum, expected %d\n", getChecksum(packet));
            //******STUDENT WORK******
            serverSend(sockfd, address, sizeof(*address), !seqnum);
        } else if (packet.header.seq_ack != seqnum) {
            printf("Bad seqnum, expected %d\n", seqnum);
            //******STUDENT WORK******
            serverSend(sockfd, address, sizeof(*address), !seqnum);
        } else {
            printf("Good packet\n");
            //******STUDENT WORK******
            serverSend(sockfd, address, sizeof(*address), seqnum);
            break;
        }
    }
    printf("\n");
    return packet;
}

int main(int argc, char *argv[]) {
    // check arguments
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <port> <outfile>\n", argv[0]);
        exit(1);
    }

    // seed the RNG
    srand((unsigned)time(NULL));

    // create a socket
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    // initialize the server address structure
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = htonl(INADDR_ANY);
    address.sin_port = htons(atoi(argv[1]));
    int addrlen = sizeof(address);

    // bind the socket
    bind(sockfd, (struct sockaddr*)&address, sizeof(address));

    // open file using argv[2]
    int fp=open(argv[2],O_CREAT | O_RDWR,0666);
    if(fp<0){
	    perror("file failed to open\n");
	    exit(1);
    }
    // get file contents from client and save it to the file
    int seqnum = 0;
    Packet packet;
    do {
        packet = serverReceive(sockfd, (struct sockaddr*)&address, &addrlen, seqnum);
        write(fp, packet.data, packet.header.len);
        seqnum = (seqnum + 1)%2;
    } while (packet.header.len != 0);

    //cleanup
    //******STUDENT WORK******
    close(sockfd);
    close(fp);
    return 0;
}
