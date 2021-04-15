
/* * Name: Dillon Kanai 
* Date: 2/4/2021
* Title: Lab5 Server
* Description: Receive a file from a client using Stop and Wait and send ACKs*/

//Lab5 Server
#include "lab5.h"

//getChecksum()
int getChecksum(Packet packet) {
    packet.header.cksum = 0;
    int checksum = 0;
    char *ptr = (char *)&packet;
    char *end = ptr + sizeof(Header) + packet.header.len;
//Find the error (if any) from the remaining part getChecksum() function and correct it
//******STUDENT WORK****** 
    while (ptr < end) {
        checksum ^= *ptr++;
    }
    return checksum;
}

// printPacket()
void printPacket(Packet packet) {
    printf("Packet{ header: { seq_ack: %d, len: %d, cksum: %d }, data: \"",
            packet.header.seq_ack,
            packet.header.len,
            packet.header.cksum);
    fwrite(packet.data, (size_t)packet.header.len, 1, stdout);
    printf("\" }\n");
}

//Server sending ACK to the client
void serverSend(int sockfd, const struct sockaddr *address, socklen_t addrlen, int seqnum) {
    Packet packet;
	//Prepare the packet headers
	//send the packet
    //******Student Work******
    packet.header.seq_ack = seqnum;
    packet.header.len = sizeof(packet.data);
    packet.header.cksum = getChecksum(packet);

    sendto(sockfd, &packet, sizeof(packet), 0, address, addrlen);
		
    printf("\t Server: sending ACK %d, checksum %d\n", packet.header.seq_ack, packet.header.cksum);
}

//Server receiving packet
Packet serverReceive(int sockfd, struct sockaddr *address, socklen_t *addrlen, int seqnum) {
    Packet packet;
    while (1) {
        //recv packets from the client
		//******Student Work******
        recvfrom(sockfd, &packet, sizeof(packet), 0, address, addrlen);

        // Print received packet
        printPacket(packet);

        if (packet.header.cksum != getChecksum(packet)) {
            printf("Bad checksum, expected checksum was: %d\n", getChecksum(packet));
            serverSend(sockfd, address, *addrlen, !seqnum);
        } else if (packet.header.seq_ack != seqnum) {
            printf("Bad seqnum, expected sequence number was:%d\n", seqnum);
            //******STUDENT WORK******
            serverSend(sockfd, address, *addrlen, !seqnum);
        } else {
            printf("Good packet\n");
            //**********STUDENT WORK******
            serverSend(sockfd, address, *addrlen, seqnum);
            break;
        }
    }
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
    int socket_fd;
    // create a socket
	if ((socket_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0){
        printf("Error: Could not make socket\n");
        return 0;
    }
    // initialize the server address structure using argv[1]
    struct sockaddr_in address;
	address.sin_family = AF_INET;
    address.sin_addr.s_addr = htonl(INADDR_ANY);
    address.sin_port = htons(atoi(argv[1]));
    char* fname = argv[2];
    socklen_t addrlen = sizeof(address);
    // bind the socket
	// [Question]: Do we need to bind the socket on the client side? Why?/Why not?
	//No, client doesn't need to provide a target to the server because the server can look at the src headers. 
    //The server does need to bind so that theclient knows where to send the packet/where to innitiate connection with.
    if (bind(socket_fd, (struct sockaddr*)&address, sizeof(address)) < 0){
        printf("Error: Failed to bind\n");
        return 0;
    }

    // open file using argv[2]
	//******STUDENT WORK******
    FILE* fp = fopen(fname, "w");

    // get file contents from client
    int seqnum = 0;
    Packet packet;
    packet.header.len = 1;
    struct sockaddr_in clientaddr;
    socklen_t clientaddr_len = sizeof(clientaddr);
    while(packet.header.len != 0){
        packet = serverReceive(socket_fd, (struct sockaddr*)&address, &addrlen, seqnum);
	    //******STUDENT WORK******
        fwrite(packet.data, packet.header.len, 1, fp);
        seqnum = (seqnum + 1) % 2;
    }
    fclose(fp);
    close(socket_fd);
    return 0;
}
