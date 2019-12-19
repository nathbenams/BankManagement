//
//  listAccount.cpp
//  Targilratouv2
//
//  Created by Nathan Benamou on 16/12/2019.
//  Copyright © 2019 Nathan Benamou. All rights reserved.
//

#include "listAccount.hpp"

//*************************************************************************************************************************************************//



//*************************************************************************************************************************************************//

ListAccount::    ~ListAccount(){
	listOfAccount.clear();
}


//*************************************************************************************************************************************************//


int ListAccount:: addAccount(int id,char* password,int balance){ //returns 0 for success , (-1) for failure
	
	//assuming that the lock is from the user
	//writeLockAccount();////locks the list! ////  maybe we are doing it from the outside... check....
	
	if (! findAccount(id)){// this id already exists for aonther account
		
		return (-1);
	}
	if (balance<0){// invalid balance
		return (-1);
	}
	Account* new_node = new Account(id,password,balance);
	int inserted=0;
    Account* cur_node;
	for (vector<Account*>::iterator it = listOfAccount.begin(); it < listOfAccount.end(); it++){
		cur_node= *it;
		if ( (cur_node->getID()) > id && !inserted){//// the first acoount with a greater id then the new account. this is the right place for the new account
			listOfAccount.insert(it,new_node);
			inserted=1;
		}
		
	}
	
	if (inserted == 0){////the new acoount has a greater id than all the other accounts. the new acoount should be added in the end of the list
	listOfAccount.insert(listOfAccount.end(),new_node);
	}
	
	//writeUnlockAccount(); //// unlocks the list  ////  maybe we are doing it from the outside... check....
	return 0;
}


//*************************************************************************************************************************************************//


Account* ListAccount:: findAccount(int id){ //// searches for an count with accountID == id, returns a pointer to the account if found or NULL else
	//assuming that th look is from outside
	//readLockAccount(); //// locks the list , reads  ////  maybe we are doing it from the outside... check....
	int index=0;
    Account *cur_node;
	for (vector<Account*>::iterator it=listOfAccount.begin(); it < listOfAccount.end(); it++){
		cur_node=listOfAccount.at(index);
		if ( (cur_node->getID()) == id){//// the wanted id is found
			//readUnlockAccount(); //unlocks the account  ////  maybe we are doing it from the outside... check....
			return(cur_node);
		}
		index++;
	}
	//readUnlockAccount(); 
	return NULL; //// if we are here, than the account was not found!
}

//*************************************************************************************************************************************************//

unsigned long ListAccount::sizeList(){
	return ( listOfAccount.size());
}




Account* ListAccount:: getAccount(unsigned long i){ ////returns a pointer to list number i or null if i is greater or equal to the list's size
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
