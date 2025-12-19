/**
 * Title: ContactServiceTest.java
 * Purpose: Unit tests for validating the functionality of the ContactService class
 * Created By: Tyler Hubbell
 * Last Updated: 11/11/2025
 */

import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.*;

public class ContactServiceTest {

    // Verify a contact can be successfully added to the service
    @Test
    void testAddContact() {

        ContactService service = new ContactService();
        Contact contact = new Contact("MM001", "Mickey", "Mouse", "4075551940", "1 Disney Castle Way");

        service.addContact(contact);

        assertEquals(1, service.getContactList().size());
    }


    // Verify that deleting a contact removes it from the service list
    @Test
    void testDeleteContact() {

        ContactService service = new ContactService();
        Contact contact = new Contact("MM001", "Minnie", "Mouse", "3215552020", "2 Magic Kingdom Ln");

        service.addContact(contact);
        service.deleteContact("MM001");

        assertTrue(service.getContactList().isEmpty());
    }


    // Validate that updates modify all mutable fields correctly
    @Test
    void testUpdateContact() {

        ContactService service = new ContactService();
        Contact contact = new Contact("MM001", "Minnie", "Mouse", "3215552020", "2 Magic Kingdom Ln");

        service.addContact(contact);
        service.updateContact("MM001", "Daisy", "Duck", "5557778888", "4 Dreamlight Path");

        Contact updated = service.getContactList().get(0);

        assertEquals("Daisy", updated.getFirstName());
        assertEquals("Duck", updated.getLastName());
        assertEquals("5557778888", updated.getPhone());
        assertEquals("4 Dreamlight Path", updated.getAddress());
    }


    // Ensure that adding a duplicate contact ID results in an exception
    @Test
    void testAddDuplicateContactThrowsError() {

        ContactService service = new ContactService();
        Contact contact1 = new Contact("MM001", "Mickey", "Mouse", "4075551940", "1 Disney Castle Way");
        Contact contact2 = new Contact("MM001", "Donald", "Duck", "4075552020", "3 Toon Town Blvd");

        service.addContact(contact1);

        assertThrows(IllegalArgumentException.class, () -> service.addContact(contact2));
    }
}
