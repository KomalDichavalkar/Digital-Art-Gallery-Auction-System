#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <limits>
#include <algorithm>
#include <iomanip>

struct Artwork {
    int art_id;
    std::string title;
    std::string artist;
    double base_price;
    double current_bid;
};

struct Bid {
    int bid_id;
    int art_id;
    std::string bidder;
    double bid_amount;
};

std::vector<Artwork> artworks;
std::vector<Bid> bids;

const std::string ART_FILE = "artworks.csv";
const std::string BID_FILE = "bids.csv";

// Helper: split CSV line
std::vector<std::string> split(const std::string& line, char delim = ',') {
    std::vector<std::string> tokens;
    std::stringstream ss(line);
    std::string item;
    while (getline(ss, item, delim)) tokens.push_back(item);
    return tokens;
}

// Load artworks
void load_artworks() {
    std::ifstream file(ART_FILE);
    if (!file) return;

    std::string line;
    getline(file, line); // skip header
    while (getline(file, line)) {
        auto tokens = split(line);
        if (tokens.size() != 5) continue;
        Artwork a;
        a.art_id = stoi(tokens[0]);
        a.title = tokens[1];
        a.artist = tokens[2];
        a.base_price = stod(tokens[3]);
        a.current_bid = stod(tokens[4]);
        artworks.push_back(a);
    }
}

// Save artworks
void save_artworks() {
    std::ofstream file(ART_FILE);
    file << "art_id,title,artist,base_price,current_bid\n";
    for (auto& a : artworks)
        file << a.art_id << "," << a.title << "," << a.artist << "," << a.base_price << "," << a.current_bid << "\n";
}

// Load bids
void load_bids() {
    std::ifstream file(BID_FILE);
    if (!file) return;

    std::string line;
    getline(file, line); // skip header
    while (getline(file, line)) {
        auto tokens = split(line);
        if (tokens.size() != 4) continue;
        Bid b;
        b.bid_id = stoi(tokens[0]);
        b.art_id = stoi(tokens[1]);
        b.bidder = tokens[2];
        b.bid_amount = stod(tokens[3]);
        bids.push_back(b);
    }
}

// Save bids
void save_bids() {
    std::ofstream file(BID_FILE);
    file << "bid_id,art_id,bidder,bid_amount\n";
    for (auto& b : bids)
        file << b.bid_id << "," << b.art_id << "," << b.bidder << "," << b.bid_amount << "\n";
}

// Add artwork
void add_artwork() {
    Artwork a;
    a.art_id = artworks.empty() ? 1 : artworks.back().art_id + 1;
    std::cout << "Enter Title: ";
    std::getline(std::cin, a.title);
    std::cout << "Enter Artist: ";
    std::getline(std::cin, a.artist);
    std::cout << "Enter Base Price: ";
    std::cin >> a.base_price;
    std::cin.ignore();
    a.current_bid = a.base_price;
    artworks.push_back(a);
    save_artworks();
    std::cout << "\n? Artwork added successfully with ID " << a.art_id << "\n";
}

// Show artworks
void show_artworks() {
    if (artworks.empty()) {
        std::cout << "\n?? No artworks available.\n";
        return;
    }

    std::cout << "\n================== ARTWORKS ==================\n";
    std::cout << std::left << std::setw(5) << "ID"
              << std::setw(25) << "Title"
              << std::setw(20) << "Artist"
              << std::setw(12) << "Base Price"
              << std::setw(12) << "Current Bid" << "\n";
    std::cout << "---------------------------------------------\n";

    for (auto& a : artworks)
        std::cout << std::setw(5) << a.art_id
                  << std::setw(25) << a.title
                  << std::setw(20) << a.artist
                  << std::setw(12) << a.base_price
                  << std::setw(12) << a.current_bid << "\n";
    std::cout << "=============================================\n";
}

// Place bid
void place_bid() {
    int id;
    std::string bidder;
    double amount;
    std::cout << "Enter Artwork ID: ";
    std::cin >> id;
    std::cin.ignore();
    std::cout << "Enter Bidder Name: ";
    std::getline(std::cin, bidder);
    std::cout << "Enter Bid Amount: ";
    std::cin >> amount;
    std::cin.ignore();

    auto it = std::find_if(artworks.begin(), artworks.end(), [id](Artwork& a) { return a.art_id == id; });
    if (it == artworks.end()) { std::cout << "? Artwork not found.\n"; return; }
    if (amount <= it->current_bid) { std::cout << "?? Bid must be higher than current bid.\n"; return; }

    it->current_bid = amount;
    Bid b;
    b.bid_id = bids.empty() ? 1 : bids.back().bid_id + 1;
    b.art_id = id;
    b.bidder = bidder;
    b.bid_amount = amount;
    bids.push_back(b);

    save_artworks();
    save_bids();
    std::cout << "? Bid placed successfully!\n";
}

// View all bids
void view_bids() {
    if (bids.empty()) { std::cout << "\n?? No bids yet.\n"; return; }

    std::cout << "\n================== ALL BIDS ==================\n";
    std::cout << std::left << std::setw(5) << "ID"
              << std::setw(8) << "ArtID"
              << std::setw(20) << "Bidder"
              << std::setw(10) << "Amount" << "\n";
    std::cout << "---------------------------------------------\n";
    for (auto& b : bids)
        std::cout << std::setw(5) << b.bid_id
                  << std::setw(8) << b.art_id
                  << std::setw(20) << b.bidder
                  << std::setw(10) << b.bid_amount << "\n";
    std::cout << "=============================================\n";
}

// View details for one artwork
void view_artwork_details() {
    int id;
    std::cout << "Enter Artwork ID: ";
    std::cin >> id;
    std::cin.ignore();

    auto it = std::find_if(artworks.begin(), artworks.end(), [id](Artwork& a) { return a.art_id == id; });
    if (it == artworks.end()) { std::cout << "? Artwork not found.\n"; return; }

    std::cout << "\n?? Artwork Details:\n";
    std::cout << "Title: " << it->title << "\nArtist: " << it->artist
              << "\nBase Price: " << it->base_price
              << "\nCurrent Bid: " << it->current_bid << "\n";

    std::cout << "\n?? Bids for this Artwork:\n";
    bool hasBid = false;
    for (auto& b : bids) {
        if (b.art_id == id) {
            std::cout << " - " << b.bidder << " : " << b.bid_amount << "\n";
            hasBid = true;
        }
    }
    if (!hasBid) std::cout << "No bids yet.\n";
}

// Delete artwork
void delete_artwork() {
    int id;
    std::cout << "Enter Artwork ID to delete: ";
    std::cin >> id;
    std::cin.ignore();

    auto it = std::remove_if(artworks.begin(), artworks.end(), [id](Artwork& a) { return a.art_id == id; });
    if (it == artworks.end()) { std::cout << "? Artwork not found.\n"; return; }

    artworks.erase(it, artworks.end());
    bids.erase(std::remove_if(bids.begin(), bids.end(), [id](Bid& b) { return b.art_id == id; }), bids.end());

    save_artworks();
    save_bids();
    std::cout << "? Artwork and its bids deleted.\n";
}

// Show top artwork
void show_top_artwork() {
    if (artworks.empty()) { std::cout << "?? No artworks.\n"; return; }

    auto max_it = std::max_element(artworks.begin(), artworks.end(), [](Artwork& a, Artwork& b) {
        return a.current_bid < b.current_bid;
    });

    std::cout << "\n?? Top Artwork:\n";
    std::cout << "ID: " << max_it->art_id << "\nTitle: " << max_it->title
              << "\nArtist: " << max_it->artist
              << "\nHighest Bid: " << max_it->current_bid << "\n";
}

// Menu
int main() {
    load_artworks();
    load_bids();

    while (true) {
        std::cout << "\n========= DIGITAL ART GALLERY & AUCTION =========\n";
        std::cout << "1. Add Artwork\n";
        std::cout << "2. Show All Artworks\n";
        std::cout << "3. Place a Bid\n";
        std::cout << "4. View All Bids\n";
        std::cout << "5. View Artwork Details\n";
        std::cout << "6. Delete Artwork\n";
        std::cout << "7. Show Top Artwork\n";
        std::cout << "8. Exit\n";
        std::cout << "=================================================\n";
        std::cout << "Enter choice: ";

        int choice;
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Invalid input.\n";
            continue;
        }
        std::cin.ignore();

        switch (choice) {
            case 1: add_artwork(); break;
            case 2: show_artworks(); break;
            case 3: place_bid(); break;
            case 4: view_bids(); break;
            case 5: view_artwork_details(); break;
            case 6: delete_artwork(); break;
            case 7: show_top_artwork(); break;
            case 8: std::cout << "?? Exiting...\n"; return 0;
            default: std::cout << "Invalid choice.\n";
        }
    }
}
