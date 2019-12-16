//
//  listAccount.cpp
//  Targilratouv2
//
//  Created by Nathan Benamou on 16/12/2019.
//  Copyright © 2019 Nathan Benamou. All rights reserved.
//

#include "listAccount.hpp"

//*************************************************************************************************************************************************//

ListAccount::	ListAccount(){
	//// i think vector initializes itself, check about the mutex
}


//*************************************************************************************************************************************************//

ListAccount::    ~ListAccount(){
	listOfAccount.clear();
}


//*************************************************************************************************************************************************//


int ListAccount:: addAccount(int id,int password,int balance){ //returns 0 for success , -1 for failure
	
	writeLockAccount();////locks the list! ////  maybe we are doing it from the outside... check....
	
	if (! findAccount(id)){// this id already exists for aonther account
		log.txt<< "Error " << id<< ":your transaction failed - account with the same id exists\n"
		return (-1);
	}
	if (balance<0){// invalid balance
		return (-1);
	}
	Account* new_node = new Account(id,password,balance);
	int inserted=0;
	int index=0;
	for (auto it=listOfAccount.begin(); it < listOfAccount.end(); it++){
		Account *cur_node=listOfAccount.at(index);
		if ( (cur_node->accountID) > id){//// the first acoount with a greater id then the new account. this is the right place for the new account
			listOfAccount.insert(it,new_node);
			inserted=1;
		}
		index++;
	}
	
	if (inserted == 0){////the new acoount has a greater id than all the other accounts. the new acoount should be added in the end of the list
	listOfAccount.insert(listOfAccount.end(),new_node);
	}
	
	writeUnlockAccount(); //// unlocks the list  ////  maybe we are doing it from the outside... check....
	return 0;
}


//*************************************************************************************************************************************************//


Account* ListAccount:: findAccount(int id){ //// searches for an count with accountID == id, returns a pointer to the account if found or NULL else
	readLockAccount(); //// locks the list , reads  ////  maybe we are doing it from the outside... check....
	int index=0;
	for (auto it=listOfAccount.begin(); it < listOfAccount.end(); it++){
		Account *cur_node=listOfAccount.at(index);
		if ( (cur_node->accountID) == id){//// the wanted id is found
			readUnlockAccount(); //unlocks the account  ////  maybe we are doing it from the outside... check....
			return(cur_node);
		}
		index++;
	}
	return NULL; //// if we are here, than the account was not found!
}

//*************************************************************************************************************************************************//

unsigned long ListAccount::sizeList(){
	return ( listOfAccount.size());
}




Account* ListAccount:: getAccount(int i){ ///returns a pointer to list number i or null if i is greater or equal to the list's size
	if (i >= listOfAccount.size()) //// boundry check, ( i put " >= " instead of " > " after checking the internet....
		return NULL;
	else 
		return( listOfAccount.at(i));
}



//*************************************************************************************************************************************************//

void ListAccount::readLockAccount(){
	ReaderWriter.enterReader();
}


//*************************************************************************************************************************************************//


void ListAccount::readUnlockAccount(){
	ReaderWriter.leaveReader();
}

//*************************************************************************************************************************************************//


void ListAccount::writeLockAccount(){
	ReaderWriter.enterWriter();
}


//*************************************************************************************************************************************************//


void ListAccount::writeUnlockAccount(){
	ReaderWriter.leaveWriter();
}

//*************************************************************************************************************************************************//
//*************************************************************************************************************************************************//
//*************************************************************************************************************************************************//