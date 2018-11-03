#include <iostream>
#include <string>

using namespace std;

class Quote{
  public:
      Quote() = default;
      Quote(const string &book, double sales_price):bookNo(book),price(sales_price){}
      Quote(const Quote&);
      string isbn() const;
      virtual double net_price(size_t n) const = 0;
      virtual ~Quote() = default;
      static void statmem();
      virtual Quote* clone() const& { return new Quote(*this);}
      virtual Quote* clone() && { return new Quote(std::move(*this));}

  private:
      string bookNo;
  protected:
      double price = 0.0;
};

class Bulk_quote:public Quote{
  public:
      Bulk_quote() = default;
      Bulk_quote(const string&,double,size_t,double);
      Bulk_quote* clone() const&{return new Bulk_quote(*this);}
      Bulk_quote* clone() && {return new Bulk_quote(std::move(*this));}
      double net_price(size_t) const override;
      void fcn(const Bulk_quote&);
  private:
      size_t min_qty = 0;
      double discount = 0.0;
};
double Bulk_quote::net_price(size_t cnt) const {
  if(cnt >= min_qty)
      return cnt * (1-discount)*price;
  else
      return cnt * price;
}

void Bulk_quote::fcn(const Bulk_quote &bulk_quote){
  Quote::statmem();
  Bulk_quote::statmem();
  bulk_quote.statmem();
  statmem();
}
