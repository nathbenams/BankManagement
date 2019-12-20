//
//  listAccount.cpp
//  Targilratouv2
//
//  Created by Nathan Benamou on 16/12/2019.
//  Copyright © 2019 Nathan Benamou. All rights reserved.
//

#include "listAccount.hpp"

//*************************************************************************************************************************************************//
ListAccount::ListAccount()
{
    listOfAccount.clear();
}



ListAccount::    ~ListAccount(){
	listOfAccount.clear();
}


//********************************************
// function name: addAccount
// Description: add an account in the list of accounts
// Parameters: parameters to create a new account
// Returns: returns 0 for success , (-1) for failure
//********************************************


int ListAccount:: addAccount(int id,char* password,int balance){
	
	
	if ( findAccount(id)){// this id already exists for aonther account
		
		return (-1);
	}
	if (balance<0){
		return (-1);
	}
	Account* new_node = new Account(id,password,balance);
	int inserted=0;
    vector<Account*>::iterator it = listOfAccount.begin();
    Account* cur_node;
	for (unsigned long index =0; index < listOfAccount.size(); index++){
		cur_node= listOfAccount.at(index);
        if(cur_node!=NULL){
            if ( (cur_node->getID()) > id && !inserted){//// the first acoount with a greater id then the new account. this is the right place for the new account
                listOfAccount.insert(it,new_node);
                inserted=1;
            }
        }
        it++;
	}
	
	if (inserted == 0){////the new acoount has a greater id than all the other accounts. the new acoount should be added in the end of the list
	listOfAccount.insert(listOfAccount.end(),new_node);
	}
	
	return 0;
}


//********************************************
// function name:findAccount
// Description: searches for an count with accountID == id, returns a pointer to the account if found or NULL else
// Parameters: id of the wnted account
// Returns: pointer on the account
//********************************************

Account* ListAccount:: findAccount(int id){
	int index=0;
    Account *cur_node;
	for (vector<Account*>::iterator it=listOfAccount.begin(); it < listOfAccount.end(); it++){
		cur_node=listOfAccount.at(index);
		if ( (cur_node->getID()) == id){//// the wanted id is found
			return(cur_node);
		}
		index++;
	}
	return NULL; //// if we are here, than the account was not found!
}


unsigned long ListAccount::sizeList(){
	return ( listOfAccount.size());
}


//********************************************
// function name: getAccount
// Description:
// Parameters: the position of the account in the list
// Returns: returns a pointer to list number i or null if i is greater or equal to the list's size
//********************************************

Account* ListAccount:: getAccount(unsigned long i){
	if (i >= listOfAccount.size()) //// boundry check, ( i put " >= " instead of " > " after checking the internet....
		return NULL;
	else 
		return( listOfAccount.at(i));
}



//********************************************
// function name: readLockAccount
// Description: lock the reders's locker
// Parameters:
// Returns:
//********************************************
void ListAccount::readLockAccount(){
	ReaderWriter.enterReader();
}


//********************************************
// function name: readUnlockAccount
// Description: release the reader's locker of the list
// Parameters:
// Returns:
//********************************************

void ListAccount::readUnlockAccount(){
	ReaderWriter.leaveReader();
}

//********************************************
// function name: writeLockAccount
// Description: lock the writer's locker of the list
// Parameters:
// Returns:
//********************************************

void ListAccount::writeLockAccount(){
	ReaderWriter.enterWriter();
}

//********************************************
// function name: writeUnlockAccount
// Description: unlock the writer's locker
// Parameters:
// Returns:
//********************************************


void ListAccount::writeUnlockAccount(){
	ReaderWriter.leaveWriter();
}

