#include <iostream>
#include <string>

using namespace std;

struct Song
{
    int id;
    string title;
    string artist;
    Song(int i = 0, string t = "", string a = "") : id(i), title(t), artist(a) {}
};

class Node
{
public:
    Song data;
    Node *next;
    bool isPlaying;

    Node(Song s)
    {
        data = s;
        next = NULL;
        isPlaying = false;
    }
};

class PlayList
{
private:
    Node *head;

    Node *getPlayingNode()
    {
        if (!head)
            return NULL;
        Node *temp = head;
        do
        {
            if (temp->isPlaying)
                return temp;
            temp = temp->next;
        } while (temp != head);
        return NULL;
    }

public:
    PlayList() { head = NULL; }

    void addNode(Song s)
    {
        Node *newNode = new Node(s);
        if (!head)
        {
            head = newNode;
            head->next = head;
        }
        else
        {
            Node *tail = head;
            while (tail->next != head)
            {
                tail = tail->next;
            }
            tail->next = newNode;
            newNode->next = head;
        }
    }

    void deleteSong(int id)
    {
        if (!head)
            return;
        Node *curr = head;
        Node *prev = NULL;

        while (curr->data.id != id)
        {
            if (curr->next == head)
            {
                cout << "Delete failed: ID " << id << " not found." << endl;
                return;
            }
            prev = curr;
            curr = curr->next;
        }

        if (curr->next == head && curr == head)
        {
            delete curr;
            head = NULL;
        }
        else if (curr == head)
        {
            Node *tail = head;
            while (tail->next != head)
                tail = tail->next;
            head = head->next;
            tail->next = head;
            delete curr;
        }
        else
        {
            prev->next = curr->next;
            delete curr;
        }
        cout << "Deleted Song ID: " << id << endl;
    }

    void deleteSong(string title)
    {
        if (!head)
            return;
        Node *temp = head;
        do
        {
            if (temp->data.title == title)
            {
                deleteSong(temp->data.id);
                return;
            }
            temp = temp->next;
        } while (temp != head);
        cout << "Delete failed: Title '" << title << "' not found." << endl;
    }

    void deleteCurrent()
    {
        Node *playing = getPlayingNode();
        if (playing)
        {
            cout << "Deleting currently playing song: " << playing->data.title << endl;
            deleteSong(playing->data.id);
        }
        else
        {
            cout << "No song is currently playing." << endl;
        }
    }

    void iterateSongList()
    {
        if (!head)
        {
            cout << "[Empty Playlist]" << endl;
            return;
        }
        Node *temp = head;
        cout << "\n--- CURRENT PLAYLIST ---" << endl;
        do
        {
            cout << "ID: " << temp->data.id << " | " << temp->data.title << " (" << temp->data.artist << ")";
            if (temp->isPlaying)
                cout << " [PLAYING ♫]";
            cout << endl;
            temp = temp->next;
        } while (temp != head);
        cout << "------------------------\n";
    }

    void playSong(int id)
    {
        if (!head)
            return;
        Node *temp = head;
        bool found = false;
        do
        {
            if (temp->data.id == id)
            {
                temp->isPlaying = true;
                found = true;
                cout << ">>> NOW PLAYING: " << temp->data.title << endl;
            }
            else
            {
                temp->isPlaying = false;
            }
            temp = temp->next;
        } while (temp != head);

        if (!found)
            cout << "Song ID " << id << " not found." << endl;
    }

    void nextSong()
    {
        if (!head)
            return;
        Node *curr = getPlayingNode();
        if (!curr)
        {
            playSong(head->data.id);
            return;
        }
        curr->isPlaying = false;
        curr->next->isPlaying = true;
        cout << ">>> NEXT: " << curr->next->data.title << endl;
    }

    void prevSong()
    {
        if (!head)
            return;
        Node *curr = getPlayingNode();
        if (!curr)
        {
            playSong(head->data.id);
            return;
        }
        Node *prev = head;
        while (prev->next != curr)
        {
            prev = prev->next;
        }
        curr->isPlaying = false;
        prev->isPlaying = true;
        cout << ">>> PREV: " << prev->data.title << endl;
    }

    void repeatSongs(int id, int count)
    {
        if (!head)
            return;

        if (id == -1)
        {
            cout << "\n[REPEAT ALL LIST: " << count << " times]" << endl;
            Node *startNode = head;
            for (int i = 0; i < count; i++)
            {
                cout << "--- Loop " << i + 1 << " ---" << endl;
                Node *t = head;
                do
                {
                    cout << "Playing: " << t->data.title << endl;
                    t = t->next;
                } while (t != head);
            }
        }
        else
        {
            Node *temp = head;
            bool found = false;
            do
            {
                if (temp->data.id == id)
                {
                    found = true;
                    cout << "\n[REPEAT SONG: " << temp->data.title << " (" << count << " times)]" << endl;
                    for (int i = 0; i < count; i++)
                    {
                        cout << "Playing (" << i + 1 << "): " << temp->data.title << endl;
                    }
                    break;
                }
                temp = temp->next;
            } while (temp != head);

            if (!found)
                cout << "Song ID " << id << " not found to repeat." << endl;
        }
    }
};

int main()
{
    PlayList myIPod;

    cout << "1. ADDING 10 SONGS..." << endl;
    myIPod.addNode(Song(1, "Lac Troi", "Son Tung MTP"));
    myIPod.addNode(Song(2, "Em Cua Ngay Hom Qua", "Son Tung MTP"));
    myIPod.addNode(Song(3, "Nang Tho", "Hoang Dung"));
    myIPod.addNode(Song(4, "Shape of You", "Ed Sheeran"));
    myIPod.addNode(Song(5, "Despacito", "Luis Fonsi"));
    myIPod.addNode(Song(6, "See You Again", "Wiz Khalifa"));
    myIPod.addNode(Song(7, "Attention", "Charlie Puth"));
    myIPod.addNode(Song(8, "Hoa No Khong Mau", "Hoai Lam"));
    myIPod.addNode(Song(9, "Mang Tien Ve Cho Me", "Den Vau"));
    myIPod.addNode(Song(10, "Waiting For You", "Mono"));

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

    return 0;
}