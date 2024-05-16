#include "contact.h"
#include <stdlib.h>
#include <assert.h>
#include <string.h>

nc_Contact_t* nc_Contacts = NULL;

void AddContact(nc_Contact_t* contact, nc_Contact_t** contacts)
{
	assert(contact);

	// add element to linked list
	contact->next = *contacts;

	// set head of elements to new element
	*contacts = contact;
}

void DestroyAllContacts(nc_Contact_t** contacts)
{
	if (!*contacts) return;

	nc_Contact_t* contact = *contacts;
	while (contact)
	{
		nc_Contact_t* next = contact->next;
		free(contact);
		contact = next;
	}

	*contacts = NULL;
}