///* File created by:
//* Lucas Spiker and Cory Smith
//* For:
//* Lab 3 on 10/1/2018
//* EGP-405 by Dan Buckstein
//*
//* �We certify that this work is entirely our own.
//*	The assessor of this project may reproduce
//*	this project and provide copies to other academic staff,
//*	and/or communicate a copy of this project to a plagiarism-checking service,
//*	which may retain a copy of the project on its database.�
//*/
//
//#include "Networking.h"
//#include "EventSystem.h"
//
//Networking::Networking()
//{}
//
//Networking::~Networking()
//{
//	if (peer != nullptr)
//	{
//		RakNet::RakPeerInterface::DestroyInstance(peer);
//	}
//}
//
//void Networking::init()
//{
//	// Networking
//	const unsigned int bufferSz = 512;
//
//	char str[bufferSz];
//
//	// create and return instance of peer interface
//	peer = RakNet::RakPeerInterface::GetInstance();
//
//	// global peer settings for this app
//	unsigned short serverPort = 60000;
//
//	// ask user for peer type
//	printf("(C)lient or (S)erver?\n");
//	fgets(str, bufferSz, stdin);
//
//	// start networking
//	if ((str[0] == 'c') || (str[0] == 'C'))
//	{
//		RakNet::SocketDescriptor sd;
//		peer->Startup(1, &sd, 1);
//
//
//		printf("Enter username: (max 16 characters)\n");
//		fgets(str, bufferSz, stdin);
//		username = str;
//
//		printf("Enter server IP or hit enter for 127.0.0.1\n");
//		fgets(str, bufferSz, stdin);
//
//		if (str[0] == '\n')
//		{
//			strcpy_s(str, "127.0.0.1");
//		}
//
//		isServer = false;
//		printf("Starting the client.\n");
//		peer->Connect(str, serverPort, 0, 0);
//	}
//	else
//	{
//		printf("Enter maximum number of clients: \n");
//		fgets(str, bufferSz, stdin);
//
//		unsigned int maxClients = atoi(str);
//		RakNet::SocketDescriptor sd(serverPort, 0);
//		peer->Startup(maxClients, &sd, 1);
//
//		// We need to let the server accept incoming connections from the clients
//		printf("Starting the server.\n");
//		peer->SetMaximumIncomingConnections(maxClients);
//		isServer = true;
//		username = "server";
//	}
//
//}
//
//// Main loop for handling every packet we're sent
//void Networking::HandlePackets()
//{
//	for (
//		packet = peer->Receive();
//		packet;
//		peer->DeallocatePacket(packet), packet = peer->Receive()
//		)
//	{
//		switch (packet->data[0])
//		{
//		case ID_REMOTE_DISCONNECTION_NOTIFICATION:
//			printf("Another client has disconnected.\n");
//			break;
//		case ID_REMOTE_CONNECTION_LOST:
//			printf("Another client has lost the connection.\n");
//			break;
//		case ID_REMOTE_NEW_INCOMING_CONNECTION:
//			printf("Another client has connected.\n");
//			break;
//		case ID_CONNECTION_REQUEST_ACCEPTED:
//			printf("Our connection request has been accepted.\n");
//			{
//
//				// Once the user has connected to the server, have them request a username
//				GameMessageFromUser msg[1] = { ID_GAME_MESSAGE_USERNAME_REQUEST };
//				strcpy_s(msg->playerName, username.c_str());
//
//				peer->Send((char *)msg, sizeof(GameMessageFromUser), HIGH_PRIORITY, RELIABLE_ORDERED, 0, packet->guid, false);
//
//			}
//			break;
//		case ID_GAME_MESSAGE_USERNAME_REQUEST:
//		{
//			GameMessageFromUser* usernameReq = (GameMessageFromUser*)packet->data;
//
//			std::string reqName = usernameReq->playerName;
//			reqName.pop_back();
//
//			if (reqName == player1.username
//				|| reqName == player2.username
//					|| reqName == username)
//			{
//				peer->CloseConnection(packet->systemAddress, true);
//				break;
//			}
//
//			userID newUser;
//			newUser.username = reqName;
//			newUser.guid = packet->guid;
//
//			if (player1.username == "\n")
//			{
//				player1 = newUser;
//			}
//			else
//			{
//				player2 = newUser;
//			}
//
//			printf("New user added");
//
//		}
//		break;
//		case ID_NEW_INCOMING_CONNECTION:
//			printf("A connection is incoming.\n");
//			break;
//		case ID_NO_FREE_INCOMING_CONNECTIONS:
//			printf("The server is full.\n");
//			break;
//		case ID_DISCONNECTION_NOTIFICATION:
//			if (isServer) {
//				printf("A client has disconnected.\n");
//			}
//			else {
//				printf("We have been disconnected.\n");
//			}
//			break;
//		case ID_CONNECTION_LOST:
//			if (isServer) {
//				printf("A client lost the connection.\n");
//			}
//			else {
//				printf("Connection lost.\n");
//			}
//			break;
//		default:
//			printf("Message with identifier %i has arrived.\n", packet->data[0]);
//			break;
//		}
//	}
//}