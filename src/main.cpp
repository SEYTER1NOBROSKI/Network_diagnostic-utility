#include "tracerout.h"
#include "network_utils.h"
#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage:\n"
                  << "  " << argv[0] << " whois <ip_or_domain>\n"
                  << "  " << argv[0] << " netstats <interface> <time>\n"
                  << "  " << argv[0] << " dns <hostname_or_ip>\n"
                  << "  " << argv[0] << " route\n"
                  << "  " << argv[0] << " <hostname> <interface>\n";
        return 1;
    }

    std::string command = argv[1];

    if (command == "whois") {
        if (argc < 3) {
            std::cerr << "Usage: " << argv[0] << " whois <ip_or_domain>\n";
            return 1;
        }

        std::string result = whoisLookup(std::string(argv[2]));
        std::cout << result << std::endl;
        return 0;
    }

    if (command == "netstats") {
        if (argc < 4) {
            std::cerr << "Usage: " << argv[0] << " netstats <interface> <seconds>\n";
            return 1;
        }
        std::string interface = argv[2];
        int seconds = std::atoi(argv[3]);
        monitorNetworkInterface(interface, seconds);
        return 0;
    }


    if (command == "route") {
        printRoutingTable();
        return 0;
    }

    if (command == "dns") {
        if (argc < 3) {
            std::cerr << "Usage: " << argv[0] << " dns <hostname_or_ip>\n";
            return 1;
        }
        dnsResolveAndPrint(argv[2]);
        return 0;
    }

    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <hostname> <interface>\n";
        return 1;
    }

    std::string hostname = argv[1];
    std::string interface = argv[2];

    std::cout << "Your Network Interface: " << interface << "\n";

    if (runTraceroute(hostname, interface)) {
        std::cout << "Traceroute completed.\n";
    } else {
        std::cerr << "Traceroute failed.\n";
    }

    return 0;
}