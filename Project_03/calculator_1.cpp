
// use namespace std

int main(){
    int x = 30000000;
    int tot = 0;
    while (x > 10000){
        tot += x;
        x = x / 2;
    }
    std::cout << tot;
}