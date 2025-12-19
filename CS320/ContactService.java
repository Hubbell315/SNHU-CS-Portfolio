/**
 * Title: ContactService.java
 * Purpose: Handles creation, storage, deletion, and updates of Contact objects in memory
 * Created By: Tyler Hubbell
 * Last Updated: 11/11/2025
 */

import java.util.ArrayList;
import java.util.List;

public class ContactService {

    private List<Contact> contactList = new ArrayList<>();


    // Add a new contact to the list, ensuring the contact ID is unique
    public void addContact(Contact contact) {

        for (Contact c : contactList) {
            if (c.getContactID().equals(contact.getContactID())) {
                throw new IllegalArgumentException("Contact ID already exists");
            }
        }

        contactList.add(contact);
    }


    // Delete a contact from the list using its unique contact ID
    public void deleteContact(String contactID) {

        contactList.removeIf(contact -> contact.getContactID().equals(contactID));
    }


    // Update existing contact fields by contact ID
    public void updateContact(String contactID, String firstName, String lastName, String phone, String address) {

        for (Contact contact : contactList) {
            if (contact.getContactID().equals(contactID)) {

                if (firstName != null) contact.setFirstName(firstName);
                if (lastName != null) contact.setLastName(lastName);
                if (phone != null) contact.setPhone(phone);
                if (address != null) contact.setAddress(address);

                return;
            }
        }

        throw new IllegalArgumentException("Contact not found");
    }


    // Return the list of all stored contacts
    public List<Contact> getContactList() {

        return contactList;
    }
}

