#include <iostream>
#include <string>

using namespace std;

// ==========================================
// 1. CLASS SONG: Đóng gói dữ liệu bài hát
// ==========================================
class Song {
private:
    int id;
    string title;
    string artist;

public:
    // Constructor chuẩn
    Song(int id = 0, string title = "", string artist = "") 
        : id(id), title(title), artist(artist) {}

    // Getters (Chỉ cho phép xem, không cho sửa trực tiếp)
    int getId() const { return id; }
    string getTitle() const { return title; }
    string getArtist() const { return artist; }

    // Overload toán tử << để in thông tin bài hát dễ dàng hơn
    friend ostream& operator<<(ostream& os, const Song& s) {
        os << "ID: " << s.id << " | " << s.title << " (" << s.artist << ")";
        return os;
    }
};

// ==========================================
// 2. CLASS NODE: Đóng gói node của danh sách
// ==========================================
class PlayList; // Khai báo trước (Forward declaration)

class Node {
private:
    Song data;
    Node* next;
    bool isPlaying;

public:
    Node(Song s) : data(s), next(NULL), isPlaying(false) {}

    // Trao quyền cho PlayList được truy cập trực tiếp vào private của Node
    friend class PlayList;
};

// ==========================================
// 3. CLASS PLAYLIST: Quản lý logic danh sách
// ==========================================
class PlayList {
private:
    Node* head;

    // Helper method (Private): Tìm node đang phát
    Node* getPlayingNode() const {
        if (!head) return NULL;
        Node* temp = head;
        do {
            if (temp->isPlaying) return temp;
            temp = temp->next;
        } while (temp != head);
        return NULL;
    }

public:
    // Constructor
    PlayList() : head(NULL) {}

    // Destructor (QUAN TRỌNG TRONG OOP): Dọn dẹp bộ nhớ khi hủy Playlist
    ~PlayList() {
        if (!head) return;
        Node* curr = head;
        Node* nextNode = NULL;
        
        // Cắt vòng tròn ra để dễ xóa
        while (curr->next != head) {
            curr = curr->next;
        }
        curr->next = NULL; // Ngắt kết nối tail về head

        // Xóa tuần tự như danh sách đơn
        curr = head;
        while (curr != NULL) {
            nextNode = curr->next;
            delete curr;
            curr = nextNode;
        }
        cout << "[System] Playlist memory cleaned up." << endl;
    }

    void addSong(const Song& s) {
        Node* newNode = new Node(s);
        if (!head) {
            head = newNode;
            head->next = head;
        } else {
            Node* tail = head;
            while (tail->next != head) {
                tail = tail->next;
            }
            tail->next = newNode;
            newNode->next = head;
        }
    }

    void deleteSong(int id) {
        if (!head) return;
        Node* curr = head;
        Node* prev = NULL;

        // Tìm node
        while (curr->data.getId() != id) {
            if (curr->next == head) {
                cout << "Delete failed: ID " << id << " not found." << endl;
                return;
            }
            prev = curr;
            curr = curr->next;
        }

        // Xử lý xóa
        if (curr->next == head && curr == head) { // Chỉ có 1 node
            delete curr;
            head = NULL;
        } 
        else if (curr == head) { // Xóa đầu
            Node* tail = head;
            while (tail->next != head) tail = tail->next;
            head = head->next;
            tail->next = head;
            delete curr;
        } 
        else { // Xóa giữa/cuối
            prev->next = curr->next;
            delete curr;
        }
        cout << "Deleted Song ID: " << id << endl;
    }

    // Overload: Xóa theo tên (Tái sử dụng logic của xóa theo ID)
    void deleteSong(string title) {
        if (!head) return;
        Node* temp = head;
        do {
            if (temp->data.getTitle() == title) {
                // Gọi hàm xóa theo ID để tránh lặp lại code (DRY Principle)
                deleteSong(temp->data.getId());
                return;
            }
            temp = temp->next;
        } while (temp != head);
        cout << "Delete failed: Title '" << title << "' not found." << endl;
    }

    void deleteCurrent() {
        Node* playing = getPlayingNode();
        if (playing) {
            cout << "Deleting currently playing song: " << playing->data.getTitle() << endl;
            deleteSong(playing->data.getId());
        } else {
            cout << "No song is currently playing." << endl;
        }
    }

    void iterateSongList() const {
        if (!head) {
            cout << "[Empty Playlist]" << endl;
            return;
        }
        Node* temp = head;
        cout << "\n--- CURRENT PLAYLIST ---" << endl;
        do {
            // Sử dụng operator<< của Song đã overload
            cout << temp->data;         
            if (temp->isPlaying) cout << " [PLAYING ♫]";
            cout << endl;
            temp = temp->next;
        } while (temp != head);
        cout << "------------------------\n";
    }

    void playSong(int id) {
        if (!head) return;
        Node* temp = head;
        bool found = false;
        do {
            if (temp->data.getId() == id) {
                temp->isPlaying = true;
                found = true;
                cout << ">>> NOW PLAYING: " << temp->data.getTitle() << endl;
            } else {
                temp->isPlaying = false;
            }
            temp = temp->next;
        } while (temp != head);

        if (!found) cout << "Song ID " << id << " not found." << endl;
    }

    void nextSong() {
        if (!head) return;
        Node* curr = getPlayingNode();
        if (!curr) {
            playSong(head->data.getId());
            return;
        }
        curr->isPlaying = false;
        curr->next->isPlaying = true;
        cout << ">>> NEXT: " << curr->next->data.getTitle() << endl;
    }

    void prevSong() {
        if (!head) return;
        Node* curr = getPlayingNode();
        if (!curr) {
            playSong(head->data.getId());
            return;
        }
        Node* prev = head;
        while (prev->next != curr) {
            prev = prev->next;
        }
        curr->isPlaying = false;
        prev->isPlaying = true;
        cout << ">>> PREV: " << prev->data.getTitle() << endl;
    }

    void repeatSongs(int id, int count) {
        if (!head) return;

        if (id == -1) {
            cout << "\n[REPEAT ALL LIST: " << count << " times]" << endl;
            for (int i = 0; i < count; i++) {
                cout << "--- Loop " << i + 1 << " ---" << endl;
                Node* t = head;
                do {
                    cout << "Playing: " << t->data.getTitle() << endl;
                    t = t->next;
                } while (t != head);
            }
        } else {
            Node* temp = head;
            bool found = false;
            do {
                if (temp->data.getId() == id) {
                    found = true;
                    cout << "\n[REPEAT SONG: " << temp->data.getTitle() << " (" << count << " times)]" << endl;
                    for (int i = 0; i < count; i++) {
                        cout << "Playing (" << i + 1 << "): " << temp->data.getTitle() << endl;
                    }
                    break;
                }
                temp = temp->next;
            } while (temp != head);

            if (!found) cout << "Song ID " << id << " not found to repeat." << endl;
        }
    }
};

// ==========================================
// 4. MAIN FUNCTION
// ==========================================
int main() {
    PlayList myIPod;

    cout << "1. ADDING 10 SONGS..." << endl;
    // Truyền object Song ẩn danh, code gọn hơn
    myIPod.addSong(Song(1, "Lac Troi", "Son Tung MTP"));
    myIPod.addSong(Song(2, "Em Cua Ngay Hom Qua", "Son Tung MTP"));
    myIPod.addSong(Song(3, "Nang Tho", "Hoang Dung"));
    myIPod.addSong(Song(4, "Shape of You", "Ed Sheeran"));
    myIPod.addSong(Song(5, "Despacito", "Luis Fonsi"));
    myIPod.addSong(Song(6, "See You Again", "Wiz Khalifa"));
    myIPod.addSong(Song(7, "Attention", "Charlie Puth"));
    myIPod.addSong(Song(8, "Hoa No Khong Mau", "Hoai Lam"));
    myIPod.addSong(Song(9, "Mang Tien Ve Cho Me", "Den Vau"));
    myIPod.addSong(Song(10, "Waiting For You", "Mono"));

    myIPod.iterateSongList();

    cout << "\n2. PLAY & NAVIGATION TEST..." << endl;
    myIPod.playSong(8);
    myIPod.nextSong();
    myIPod.nextSong();

    cout << "\nChecking Circular Property (Next from 10 -> 1):" << endl;
    myIPod.nextSong();

    cout << "\nChecking Circular Property (Prev from 1 -> 10):" << endl;
    myIPod.prevSong();

    myIPod.iterateSongList();

    cout << "\n3. DELETION TEST..." << endl;
    myIPod.deleteSong(5);
    myIPod.deleteSong("Attention");

    cout << "\nDeleting the song currently playing (ID 10):" << endl;
    myIPod.deleteCurrent();

    myIPod.iterateSongList();

    cout << "\n4. REPEAT TEST..." << endl;
    myIPod.repeatSongs(1, 3);
    myIPod.repeatSongs(-1, 2);

    // Khi hàm main kết thúc, Destructor ~PlayList() sẽ tự động chạy để dọn RAM
    return 0;
}