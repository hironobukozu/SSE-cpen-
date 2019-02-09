#ifndef ORDER_H
#define ORDER_H


#define ORDER_TYPE_REGULAR 1
#define ORDER_TYPE_RESTOCK 2
/**
 * Basic order information containing a customer id and item id
 */
struct Order {
  int item_id;
  int quantity;
  int type;

  //bool operator==(const Order& other) const {
    //return ((customer_id == other.customer_id)
      //  && (item_id == other.item_id));
  //}

 // bool operator!=(const Order& other) const {
   // return !(*this == other);
  //}
};

#endif //LAB6_ORDER_H
