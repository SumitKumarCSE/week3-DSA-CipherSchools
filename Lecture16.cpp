#include <bits/stdc++.h>
using namespace std;

struct User {
    string name;
    string email;
    string username;
    string password;
    unordered_set<string> followers;
    unordered_set<string> following;
    vector<string> messages;
    vector<string> feed;
};

class ChatApplication {
private:
    unordered_map<string, User> users;
    unordered_map<string, string> loggedInUsers;
    
public:
    void createUser(string name, string email, string username, string password) {
        if (users.count(username) == 0) {
            User newUser;
            newUser.name = name;
            newUser.email = email;
            newUser.username = username;
            newUser.password = password;
            users[username] = newUser;
            cout << "User created successfully!" << endl;
        } else {
            cout << "Username already taken. Please choose a different username." << endl;
        }
    }
    
    void login(string username, string password) {
        if (users.count(username) == 0 || users[username].password != password) {
            cout << "Invalid username or password." << endl;
        } else {
            loggedInUsers[username] = password;
            cout << "Logged in successfully!" << endl;
        }
    }
    
    void logout(string username) {
        if (loggedInUsers.count(username) == 0) {
            cout << "User is not logged in." << endl;
        } else {
            loggedInUsers.erase(username);
            cout << "Logged out successfully!" << endl;
        }
    }
    
    void followUser(string follower, string following) {
        if (users.count(follower) == 0 || users.count(following) == 0) {
            cout << "Invalid username." << endl;
        } else {
            users[follower].following.insert(following);
            users[following].followers.insert(follower);
            cout << follower << " is now following " << following << endl;
        }
    }
    
    void unfollowUser(string follower, string following) {
        if (users.count(follower) == 0 || users.count(following) == 0) {
            cout << "Invalid username." << endl;
        } else {
            users[follower].following.erase(following);
            users[following].followers.erase(follower);
            cout << follower << " has unfollowed " << following << endl;
        }
    }
    
    void sendMessage(string sender, string receiver, string message) {
        if (users.count(sender) == 0 || users.count(receiver) == 0) {
            cout << "Invalid username." << endl;
        } else {
            users[receiver].messages.push_back(sender + ": " + message);
            cout << "Message sent successfully!" << endl;
        }
    }
    
    void sendBroadcast(string sender, string message) {
        if (users.count(sender) == 0) {
            cout << "Invalid username." << endl;
        } else {
            for (auto& user : users) {
                if (user.first != sender) {
                    user.second.messages.push_back(sender + " (Broadcast): " + message);
                }
            }
            cout << "Broadcast sent successfully!" << endl;
        }
    }
    
    void showMessages(string username) {
        if (users.count(username) == 0) {
            cout << "Invalid username." << endl;
        } else {
            cout << "Messages for " << username << ":" << endl;
            for (const string& message : users[username].messages) {
                cout << message << endl;
            }
        }
    }
    
    void showFeed(string username) {
        if (users.count(username) == 0) {
            cout << "Invalid username." << endl;
        } else {
            cout << "Feed for " << username << ":" << endl;
            for (const string& message : users[username].feed) {
                cout << message << endl;
            }
        }
    }
};

int main() {
    ChatApplication chatApp;
    
    // Create users
    chatApp.createUser("John Doe", "john@example.com", "johndoe", "password1");
    chatApp.createUser("Jane Smith", "jane@example.com", "janesmith", "password2");
    chatApp.createUser("Alice Johnson", "alice@example.com", "alicejohnson", "password3");
    
    // Login
    chatApp.login("johndoe", "password1");
    chatApp.login("janesmith", "password2");
    
    // Follow users
    chatApp.followUser("johndoe", "janesmith");
    chatApp.followUser("janesmith", "alicejohnson");
    
    // Send messages
    chatApp.sendMessage("johndoe", "janesmith", "Hi Jane!");
    chatApp.sendMessage("alicejohnson", "janesmith", "Hello Jane!");
    
    // Send broadcast
    chatApp.sendBroadcast("alicejohnson", "Greetings everyone!");
    
    // Show messages and feed
    chatApp.showMessages("janesmith");
    chatApp.showFeed("janesmith");
    
    // Logout
    chatApp.logout("johndoe");

}