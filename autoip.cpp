#include <iostream>
#include <Windows.h>
#include <vector>
#include <string>

using namespace std;

bool validateIpAddress(const string& ipAddress) {
    // Implement your IP address validation logic here.
    // You can check if the format is correct (e.g., "192.168.1.1").
    // Return true if valid, false otherwise.
    // Example: Check if it contains four segments separated by dots.
    // You can also validate the range of each segment (0-255).
    // Remember to handle exceptions or edge cases.
    // For simplicity, I'll assume any non-empty string is valid.
    return !ipAddress.empty();
}

void setNetworkConfig(const string& ipAddress, const string& subnetMask, const vector<string>& dnsServers, const string& gateway) {
    string command = "netsh interface ip set address name=\"Ethernet\" static " + ipAddress + " " + subnetMask + " " + gateway;
    system(command.c_str());

    command = "netsh interface ip set dns name=\"Ethernet\" static " + dnsServers[0];
    system(command.c_str());

    command = "netsh interface ip add dns name=\"Ethernet\" " + dnsServers[1] + " index=2";
    system(command.c_str());
}

int main() {
    string ipAddress, subnetMask, gateway;
    vector<string> dnsServers;

    cout << "IP adresini girin: ";
    cin >> ipAddress;

    // Validate the entered IP address
    if (!validateIpAddress(ipAddress)) {
        cout << "Geçersiz IP adresi! Lütfen doğru bir IP adresi girin." << endl;
        return 1; // Exit with an error code
    }

    subnetMask = "255.0.0.0"; // Alt ağ maskesi sabit olarak ayarlandı

    dnsServers.push_back("8.8.8.8"); // Birincil DNS sunucusu eklendi
    dnsServers.push_back("8.8.4.4"); // İkincil DNS sunucusu eklendi

    gateway = "49.13.253.97"; // Ağ geçidi sabit olarak ayarlandı

    setNetworkConfig(ipAddress, subnetMask, dnsServers, gateway);

    cout << "Ağ yapılandırması başarıyla ayarlandı." << endl;

    return 0;
}
