/* * Name: Dillon Kanai 
* Date: 2/4/2021
* Title: Lab5 Client
* Description: Send a file to a server using Stop and Wait and receive ACKs*/

//Lab5 Client
#include "lab5.h"

#define BUFSIZE 30

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


//clientSend()
void clientSend(int sockfd, const struct sockaddr *address, socklen_t addrlen, Packet packet) {
    
    while (1) {
        // send the packet
        printf("Client: sending packet\n");
        if (rand()%5 == 1){
            packet.header.cksum = rand()%20;
        }
        else{
            packet.header.cksum = getChecksum(packet);
        }
		sendto(sockfd, &packet, sizeof(packet), 0, address, addrlen);
        // receive an ACK from the server
        Packet recvpacket;
		//******STUDENT WORK******
        recvfrom(sockfd, &recvpacket, sizeof(recvpacket), 0, (struct sockaddr*)address, &addrlen);

        // log what was received
        printf("Received ACK %d, checksum %d - ", recvpacket.header.seq_ack, recvpacket.header.cksum);

        //print received packet
        printPacket(packet);
        // validate the ACK
        if (recvpacket.header.cksum != getChecksum(recvpacket)) {
            // bad checksum, resend packet
            printf("Bad checksum, expected checksum was: %d\n", packet.header.cksum);
        } else if (packet.header.seq_ack != recvpacket.header.seq_ack) {
            // incorrect sequence number, resend packet
            printf("Bad seqnum, expected sequence number was: %d\n", packet.header.seq_ack);
        } else {
            // good ACK, we're done
            printf("Good ACK\n");
            break;
        }
    }
}

int main(int argc, char *argv[]) {
    // check arguments
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <ip> <port> <infile>\n", argv[0]);
        return 1;
    }

    // seed the RNG
    srand((unsigned)time(NULL));

    // create and configure the socket [name the socket sockfd] 
	//******STUDENT WORK******	  
    int socket_fd = socket(AF_INET, SOCK_DGRAM, 0);  


    // initialize the server address structure using argv[2] and argv[1]
    struct sockaddr_in address;
    memset(&address, 0, sizeof(address));
	//******STUDENT WORK******
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr(argv[1]);
    address.sin_port = htons(atoi(argv[2]));
    socklen_t addr_len = sizeof(address);

    // open file using argv[3]
	//******STUDENT WORK******
    FILE* fp = fopen(argv[3], "r");

    // send file contents to server
	//-create a packet
	//-set the seq_ack field 
	//-set the len field
	//-calculate the checksum
	//-send the packet
	//******STUDENT WORK******
    int items = 0, seqnum = 0;
    Packet pack;
    while(items = fread(pack.data, 1, 10, fp)){
        pack.header.seq_ack = seqnum;
        pack.header.len = items;
        pack.header.cksum = getChecksum(pack);
        clientSend(socket_fd, (struct sockaddr*)&address, sizeof(address), pack);
        seqnum = (seqnum + 1) % 2;
    }


    // send zero-length packet to server to end connection
    Packet zero;
    zero.header.seq_ack = seqnum;
    zero.header.cksum = getChecksum(zero);
    zero.header.len = 0;
	clientSend(socket_fd, (struct sockaddr*)&address, addr_len, zero);

    // clean up
	//-close the sockets and file
    //******STUDENT WORK******
    fclose(fp);
    close(socket_fd);

    return 0;
}
