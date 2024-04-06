#include<iostream>
#include<cstring>
using namespace std;

class InvestmentPlan{
private:
    char name[80];
    double sum_investment;
    double shares_number;
    bool currentDay;
    void copy(const InvestmentPlan & ip){
        strcpy(this->name, ip.name);
        this->sum_investment = ip.sum_investment;
        this->shares_number = ip.shares_number;
        this->currentDay = ip.currentDay;
    }
public:
    InvestmentPlan() {}
    InvestmentPlan(char *name, double sumInvestment, double sharesNumber, bool currentDay) {
        strcpy(this->name, name);
        this->sum_investment = sumInvestment;
        this->shares_number = sharesNumber;
        this->currentDay = currentDay;
    }
    InvestmentPlan(const InvestmentPlan & other){
        copy(other);
    }

    int getSumInvestment() const {
        return sum_investment;
    }
};
class MoneyFund{
private:
    static double provision;
public:
    MoneyFund() {
        this->provision = 0.1;
    }

    static double getProvision() {
        return provision;
    }
};
class InvestmentFund{
private:
    char name[50];
    InvestmentPlan * investmentPlan;
    int n;
    double share_price;
    void copy(const InvestmentFund & ifn){
        strcpy(this->name, ifn.name);
        this->n = ifn.n;
        this->share_price = ifn.share_price;
        investmentPlan = new InvestmentPlan[this->n];
        for(int i = 0; i < this->n; i++){
            this->investmentPlan[i] = ifn.investmentPlan[i];
        }
    }
public:
    InvestmentFund() {}
    InvestmentFund(char *name, int n, double sharePrice){
        strcpy(this->name,name);
        this->n = n;
        investmentPlan = new InvestmentPlan[0];
    }
    InvestmentFund(const InvestmentFund & other){
        copy(other);
    }
    ~InvestmentFund(){
        delete [] investmentPlan;
    }

    double getTotalProfit(const InvestmentPlan & ip, const MoneyFund & mf){
        double sum = ((ip.getSumInvestment() * mf.getProvision() / 100)) / 365;
        return sum;
    }
    friend double dailyProfit(const InvestmentPlan & ip, const InvestmentFund & ifn, const MoneyFund & mf);
};

class ActionFund{
private:
    char name[50];
    InvestmentFund * investmentFund;
    int m;
    double udel;
    static double provision_percent;
    static double entry_provision;
    void copy(const ActionFund & af){
        strcpy(this->name, af.name);
        this->m = af.m;
        this->udel = af.udel;
        this->provision_percent = af.provision_percent;
        this->entry_provision = af.entry_provision;
        investmentFund = new InvestmentFund[this->m];
        for(int i = 0; i < this->m; i++){
            this->investmentFund[i] = af.investmentFund[i];
        }
    }
public:
    ActionFund(char * name, InvestmentFund * ip, int m, double udel) {
        strcpy(this->name, name);
        this->m = m;
        this->udel = udel;
        investmentFund = ip;
        this->provision_percent = 0.15;
        this->entry_provision = 0.3;
    }
//    ActionFund(const ActionFund & other){
//        copy(other);
//    }
    ~ActionFund(){
        delete [] investmentFund;
    }
    double dailyProfit(const InvestmentPlan & ip, InvestmentFund ifn, const MoneyFund & mf){
        double sum = (((ip.getSumInvestment() * mf.getProvision()) / 100) / 365) * entry_provision / 100;
        double dailyProfit = ifn.getTotalProfit(sum);
        return dailyProfit;
    }
};

double totalProfit(InvestmentFund** funds, int n){
    double sum = 0;
    for(int i = 0; i < n; i++){
        sum += totalProfit(&funds[i],n);
    }
    return sum;
}

//your code here


int main(){

    char investitor[80], ime[50];
    double plan, brUdeli, udel;
    bool flag = false;
    int n, m;
    cin >> n;
    InvestmentFund **fondovi = new InvestmentFund*[n];
    for(int i = 0; i < n; i++){
        cin >> ime;
        cin >> m;
        InvestmentPlan *ip = new InvestmentPlan[m];
        for(int j = 0; j < m; j++){
            cin >> investitor >> plan >> brUdeli;
            if(j % 2) flag = true;
            else flag = false;
            InvestmentPlan IP(investitor, plan, brUdeli, flag);
            ip[j] = IP;
        }
        cin >> udel;
        if(i % 2){
            fondovi[i] = new ActionFund(ime, ip, m, udel);

        }
        else{
            fondovi[i] = new MoneyFund(ime, ip, m, udel);
        }
    }
    cout << totalProfit(fondovi, n);
    return 0;
}
