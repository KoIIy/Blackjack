#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>

using namespace std;

struct Card {
    string rank;
    string suit;
    int value;
};
class Deck {
private:
    vector<string> suits = { "Черви", "Бубны", "Пики", "Крести" };
    vector<string> ranks = { "2", "3", "4", "5", "6", "7", "8", "9", "10", "Валет", "Дама", "Король", "Туз" };
	int values[13] = { 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 1 };
    
public:
    vector<Card> createDeck() {
        vector<Card> deck;
        for (int s = 0; s < 4; s++) {
            for (const auto& suit : suits) {
                int i = 0;
                for (const auto& rank : ranks) {
                    deck.push_back({ rank,suit,values[i] });
                    i++;
                }
            }
        }
        return deck;
    }
};

class BlackJackGame {
private:
    vector<Card> deck,player,dealer;
    int indexCard = 0; //Индекс следующей карты
public:
    void mixDeck() {
        shuffle(deck.begin(), deck.end(), default_random_engine(time(0)));
    }
    Card takeCard() {
        if (indexCard >= deck.size()) {
            mixDeck();
            indexCard = 0;
        }
        return deck[indexCard++];
    }
    int checkHand(const vector<Card>& hand) {
        int countAce = 0;
        int sum = 0;
        for (const auto& card : hand) {
            sum += card.value;
            if (card.rank == "Туз") {
                countAce++;
            }
        }
        while (countAce  > 0 && sum + 10 <= 21) {
            sum += 10;
            countAce--;
        }
        return sum;
    }
    void startGame() {
        system("cls");
        cout << "Добро пожаловать в игру Блэкджек!" << endl;
        cout << endl;
        while (true) {
            player.clear();
            dealer.clear();
            bool over = false; //перебор
            player.push_back(takeCard());
            dealer.push_back(takeCard());
            player.push_back(takeCard());
            dealer.push_back(takeCard());
            cout << "Первая карта дилера:" << endl;
            cout << dealer[0].rank << "\t" << dealer[0].suit << endl;
            cout << endl;
            while (true) {
                cout << "Ваши карты:" << endl;
                for (const auto& card : player) {
                    cout << card.rank << "\t" << card.suit << endl;
                }
                cout << "Очки: " << checkHand(player) << endl;
                if (checkHand(player) > 21) {
                    over = true;
                    break;
                }
                cout << "Взять карту? (y/n):";
                char choice;
                cin >> choice;
                cout << endl;
                if (choice == 'y') {
                    player.push_back(takeCard());
                }
                else {
                    break;
                }
            }
            if (!over) {
                while (17>checkHand(dealer)) {
                    dealer.push_back(takeCard());
                }
            }
            cout << "Карты дилера:" << endl;
            for (const auto& card : dealer) {
                cout << card.rank << "\t" << card.suit << endl;
            }
            cout << "Очки: " << checkHand(dealer) << endl;
            cout << endl;
            int p = checkHand(player);
            int d = checkHand(dealer);
            if (p<=21&&(p > d || d > 21))
            {
                cout << "Поздравляю вы выиграли!" << endl;
            } 
            else
            {
                if (p == d) {
                    cout << "Ничья." << endl;
                }
                else 
                {
                    cout << "Вы проиграли." << endl;
                }
            }
            cout << endl;
            cout << "Продолжить? (y/n):";
            char choice;
            cin >> choice;
            cout << endl;
            system("cls");
            if (choice == 'n') {
                break;
            }
            
        }
    }
    BlackJackGame(vector<Card> _deck) : deck(_deck) {
        mixDeck();
    }



};

int main()
{
    system("chcp 1251");
    Deck deck;
    BlackJackGame game(deck.createDeck());
    game.startGame();

}