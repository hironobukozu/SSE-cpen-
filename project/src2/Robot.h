#ifndef ROBOT_H
#define ROBOT_H

#include <cpen333/thread/thread_object.h>
#include <cpen333/process/mutex.h>
#include <cpen333/thread/semaphore.h>
#include <iostream>
#include <thread>
#include <mutex>

#define WAREHOUSE_ROWS 7
#define WAREHOUSE_COLUMNS 7
#define WAREHOUSE_SHELVES 6


#include "Order.h"
#include "OrderQueue.h"
#include "safe_printf.h"
#include "Computer.h"


 class Robot : public cpen333::thread::thread_object {
	OrderQueue& orders_;
	OrderQueue& deliver_;
	int id_;
	int col_position_ = 0 ;
	int row_position_ = 0 ;
	int side_position_ = 0;
	int shelf_position_ = 0;
	Storage& storage_;

  public:

	  Robot(int id, OrderQueue& orders, OrderQueue& deliver
		  , int col_position, int row_position, int side_position, int shelf_position, Storage& storage
	  ) :

		  id_(id), orders_(orders), deliver_(deliver)
		  , col_position_(col_position), row_position_(row_position), side_position_(side_position), shelf_position_(shelf_position), storage_(storage)
		  
		{}

   int id() {
     return id_;
   }

   
   void prepare_order(const Order& order, Storage& storage_,int col_position, int row_position, int side_position, int shelf_position,cpen333::process::mutex& mutex_){
	   int col_destination, row_destination, side_destination, shelf_destination;
	   std::string item_name;
	   for(auto object : storage_.list_){
		   if(object.id == order.item_id){
			   col_destination =  object.col_number;
			   row_destination =  object.row_number;
			   side_destination =  object.side;
			   shelf_destination = object.shelf;
			   item_name = object.name;
		   }
	   }			  
	   safe_printf("Robot %d beginning to prepare order {%s,%d}\n", id_, item_name.c_str(),order.quantity);
	   safe_printf("Robot %d moving down row\n", id_);
	   for(col_position; col_position < col_destination; col_position++){
		   std::this_thread::sleep_for(std::chrono::milliseconds(200));
	   }
	   safe_printf("Robot %d moving down column\n", id_);
	   for(row_position; row_position < row_destination; row_position++){
		   std::this_thread::sleep_for(std::chrono::milliseconds(200));
	   }
	   safe_printf("Robot %d moving turning\n", id_);
	   for(side_position ;side_position<side_destination;side_position++){
		   std::this_thread::sleep_for(std::chrono::milliseconds(200));
	   }
	   safe_printf("Robot %d reaching for shelf\n", id_);
	   for(shelf_position; shelf_position<shelf_destination; shelf_position++){
		   std::this_thread::sleep_for(std::chrono::milliseconds(200));
	   }

	   safe_printf("Got %s\n", item_name.c_str());

	   {
		   std::lock_guard<cpen333::process::mutex> mutex_();
		   storage_.storage_[order.item_id].stock = storage_.storage_[order.item_id].stock - order.quantity;
		   safe_printf("%d remaining in stock.\n", storage_.storage_[order.item_id].stock );
	   }

	   safe_printf("Robot %d coming down from shelf\n", id_);
	   for(shelf_position;shelf_position>=0;shelf_position--){
		   std::this_thread::sleep_for(std::chrono::milliseconds(200));
	   }
	   safe_printf("Robot %d facing forward\n", id_);
	   side_position = 0;
	   safe_printf("Robot %d moving down column\n", id_);
	   for(row_position; row_position<=6; row_position++){
		   std::this_thread::sleep_for(std::chrono::milliseconds(200));
	   }
	   safe_printf("Robot %d moving to loading dock\n", id_);
	   if(col_position>3){
		   for(col_position;col_position>=2;col_position--){
			   std::this_thread::sleep_for(std::chrono::milliseconds(200));
		   }
	   } else if(col_position<3){
		   for(col_position;col_position<=2;col_position++){
			   std::this_thread::sleep_for(std::chrono::milliseconds(200));
		   }
	   }

	   safe_printf("Order preapared\n");
	   deliver_.add(order);
   }

   void restock_order(const Order& order,Storage& storage, int col_position, int row_position, int side_position, int shelf_position,cpen333::process::mutex& mutex_) {
	  
	   safe_printf("Robot %d moving down row\n", id_);
	   for (col_position; col_position < 7; col_position++) {
		   std::this_thread::sleep_for(std::chrono::milliseconds(200));
	   }
	   safe_printf("Robot %d moving down column\n", id_);
	   for (row_position; row_position < 4; row_position++) {
		   std::this_thread::sleep_for(std::chrono::milliseconds(200));
	   }

	   int col_destination, row_destination, side_destination, shelf_destination;
	   std::string item_name;
	   for (auto object : storage_.list_) {
		   if (object.id == order.item_id) {
			   col_destination = object.col_number;
			   row_destination = object.row_number;
			   side_destination = object.side;
			   shelf_destination = object.shelf;
			   item_name = object.name;
		   }
	   }

	   safe_printf("Getting restock for %s from truck\n",item_name.c_str());

	   safe_printf("Robot %d moving down row\n", id_);
	   if (row_destination <= 4) {
		   for (row_position; row_position > row_destination; row_position--) {
			   std::this_thread::sleep_for(std::chrono::milliseconds(200));
		   }
	   }
	   else {
		   for (row_position; row_position < row_destination ; row_position++) {
			   std::this_thread::sleep_for(std::chrono::milliseconds(200));
		   }

	   }
	   safe_printf("Robot %d moving down column\n", id_);
	   for (col_position; col_position > col_destination; col_position--) {
		   std::this_thread::sleep_for(std::chrono::milliseconds(200));
	   }
	   safe_printf("Robot %d turning\n", id_);
	   for (side_position; side_position < side_destination; side_position++) {
		   std::this_thread::sleep_for(std::chrono::milliseconds(200));
	   }
	   safe_printf("Robot %d reaching for shelf\n", id_);
	   for (shelf_position; shelf_position < shelf_destination; shelf_position++) {
		   std::this_thread::sleep_for(std::chrono::milliseconds(200));
	   }
	   {
		   std::lock_guard<cpen333::process::mutex> mutex_();
		   storage_.storage_[order.item_id].stock = storage_.storage_[order.item_id].stock + order.quantity;
		   safe_printf("%s restocked\n", storage_.storage_[order.item_id].name.c_str());
		   safe_printf("%d remaining \n", storage_.storage_[order.item_id].stock);
	   }
	   safe_printf("Robot %d coming down fromr shelf\n", id_);
	   for (shelf_position; shelf_position >= 0; shelf_position--) {
		   std::this_thread::sleep_for(std::chrono::milliseconds(200));
	   }
	   safe_printf("Robot %d facing forward\n", id_);
	   side_position = 0;
	   safe_printf("Robot %d moving down column\n", id_);
	   for (col_position; col_position < 7; col_position++) {
		   std::this_thread::sleep_for(std::chrono::milliseconds(200));
	   }

   }

   void return_start(int col_position, int row_position,int side_position,int  shelf_position) {
	   safe_printf("Robot %d returning to start point\n", id_);

	   
	   safe_printf("Robot %d moving down row\n", id_);
	   for (row_position; row_position >= 0 ; row_position--) {
		   std::this_thread::sleep_for(std::chrono::milliseconds(200));
	   }
	   
	   safe_printf("Robot %d moving down column\n", id_);
	   for (col_position; col_position >= 0; col_position--) {
		   std::this_thread::sleep_for(std::chrono::milliseconds(200));
	   }

	   safe_printf("Robot %d back to starting position\n", id_);
   }


   int main() {

	   safe_printf("Robot %d started\n", id_);

	   cpen333::process::mutex mutex_("robot");

	   Order order = orders_.get();

	   while (order.item_id != 4000) {
		   if (order.type == ORDER_TYPE_REGULAR) {

			   prepare_order(order,std::ref(storage_),col_position_,row_position_,side_position_,shelf_position_,mutex_);
			   return_start(col_position_, row_position_, side_position_, shelf_position_);
			   order = orders_.get();
		   }
		   else {
			   safe_printf("Robot %d received restock order\n",id_);
			   restock_order(order,std::ref(storage_), col_position_, row_position_, side_position_, shelf_position_,mutex_);
			   return_start(col_position_, row_position_, side_position_, shelf_position_);
			   order = orders_.get();
		   }
	   }
	   safe_printf("Robot %d done\n", id_);
	   return 0;
   }
 };

#endif ROBoT_H
