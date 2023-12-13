#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"
#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"
#pragma ide diagnostic ignored "bugprone-unused-return-value"
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/event.h>
#include <arpa/inet.h>
#include <signal.h>

// 读取配置文件
void readConfig(std::string &address, int &port, std::string &rootDir) {
    std::ifstream config("/Users/emptyset/Projects/NetworkLab/Socket/config.txt");
    if (!config) {
        std::cerr << "Failed to open config file." << std::endl;
        return;
    }
    config >> address >> port >> rootDir;
    config.close();
}

std::string getContentType(const std::string &filePath) {
    if (filePath.ends_with(".html") || filePath.ends_with(".htm")) {
        return "text/html";
    } else if (filePath.ends_with(".css")) {
        return "text/css";
    } else if (filePath.ends_with(".js")) {
        return "application/javascript";
    } else if (filePath.ends_with(".jpg") || filePath.ends_with(".jpeg")) {
        return "image/jpeg";
    } else if (filePath.ends_with(".png")) {
        return "image/png";
    } else if (filePath.ends_with(".gif")) {
        return "image/gif";
    } else if (filePath.ends_with(".txt")) {
        return "text/plain";
    } else if (filePath.ends_with(".mp4")) {
            return "video/mp4";
    } else {
        return "application/octet-stream";
    }
}

void handleClient(int clientSocket, const std::string &rootDir) {
    char buffer[2048];
    recv(clientSocket, buffer, sizeof(buffer), 0);

    struct sockaddr_in clientAddr;
    socklen_t clientAddrLen = sizeof(clientAddr);
    getpeername(clientSocket, (struct sockaddr*)&clientAddr, &clientAddrLen);
    char clientIP[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &clientAddr.sin_addr, clientIP, sizeof(clientIP));
    int clientPort = ntohs(clientAddr.sin_port);

    std::string request(buffer);
    size_t endOfLine = request.find("\r\n");
    std::string requestLine = request.substr(0, endOfLine);
    std::cout << "Request from " << clientIP << ":" << clientPort << " - " << requestLine << std::endl;

    size_t pos = request.find("GET");
    if (pos == std::string::npos) {
        std::string response = "HTTP/1.1 400 Bad Request\r\n\r\n";
        send(clientSocket, response.c_str(), response.size(), 0);
        return;
    }

    size_t start = request.find(" ", pos) + 1;
    size_t end = request.find(" ", start);
    std::string filePath = request.substr(start, end - start);

    if (filePath == "/") {
        filePath = "/index.html";
    }

    std::string contentType = getContentType(filePath);

    std::string responseStatus;
    std::string responseBody;
    std::ifstream file(rootDir + filePath, std::ios::binary);

    bool is_open = file.is_open();
    bool good = file.good();
    if (!is_open or !good) {
        if (!is_open) {
            responseStatus = "404 Not Found";
            responseBody = "<html><body><h1>404 Not Found</h1><p>The requested file was not found on this server.</p></body></html>";
        }
        else {
            responseStatus = "500 Internal Server Error";
            responseBody = "<html><body><h1>500 Internal Server Error</h1><p>There was an error reading the requested file.</p></body></html>";
        }

        std::string response = "HTTP/1.1 " + responseStatus + "\r\n";
        response += "Content-Type: text/html\r\n\r\n";
        response += responseBody;
        send(clientSocket, response.c_str(), response.size(), 0);
        std::cout << "Response to " << clientIP << ":" << clientPort << " - " << responseStatus << std::endl;
        return;
    }

    responseStatus = "200 OK";
    std::string response = "HTTP/1.1 200 OK\r\n";
    response += "Content-Type: " + contentType + "\r\n\r\n";

    if (send(clientSocket, response.c_str(), response.size(), 0) == -1) {
        std::cerr << "Failed to send" << std::endl;
    }

    char fileBuffer[512];
    while (file.read(fileBuffer, sizeof(fileBuffer))) {
        ssize_t bytesSent = send(clientSocket, fileBuffer, file.gcount(), 0);
        if (bytesSent == -1) {
            std::cerr << "Failed to send" << std::endl;
        }
    }

    if (file.gcount() > 0) {
        ssize_t bytesSent = send(clientSocket, fileBuffer, file.gcount(), 0);
        if (bytesSent == -1) {
            std::cerr << "Failed to send" << std::endl;
        }
    }

    file.close();
    std::cout << "Response to " << clientIP << ":" << clientPort << " - " << responseStatus << std::endl;
}

int main() {
    // signal(SIGPIPE, SIG_IGN);

    std::string address, rootDir;
    int port;
    readConfig(address, port, rootDir);

    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0) {
        std::cerr << "Error: Unable to create socket." << std::endl;
        return 1;
    }

    int opt = 1;
    setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    if (bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
        std::cerr << "Error: Unable to bind to port " << port << std::endl;
        close(serverSocket);
        return 1;
    }

    if (listen(serverSocket, 5) < 0) {
        std::cerr << "Error: Unable to listen on port " << port << std::endl;
        close(serverSocket);
        return 1;
    }

    int kq = kqueue();
    if (kq < 0) {
        std::cerr << "Error: Unable to create kqueue." << std::endl;
        close(serverSocket);
        return 1;
    }

    struct kevent evSet{};
    EV_SET(&evSet, serverSocket, EVFILT_READ, EV_ADD, 0, 0, NULL);
    kevent(kq, &evSet, 1, NULL, 0, NULL);

    while (true) {
        struct kevent evList[32];
        int n = kevent(kq, NULL, 0, evList, 32, NULL);

        for (int i = 0; i < n; i++) {
            if (evList[i].ident == serverSocket) {
                int clientSocket = accept(serverSocket, NULL, NULL);
                EV_SET(&evSet, clientSocket, EVFILT_READ, EV_ADD, 0, 0, NULL);
                kevent(kq, &evSet, 1, NULL, 0, NULL);
            } else if (evList[i].flags & EVFILT_READ) {
                handleClient(evList[i].ident, rootDir);
                close(evList[i].ident);
            }
        }
    }

    close(serverSocket);
    return 0;
}
#pragma clang diagnostic pop
#pragma clang diagnostic pop