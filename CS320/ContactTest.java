/**
 * Title: ContactTest.java
 * Purpose: Unit tests for validating the Contact class functionality and data constraints
 * Created By: Tyler Hubbell
 * Last Updated: 11/11/2025
 */

import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.*;

public class ContactTest {

    // Verify that a Contact object is created successfully with valid parameters
    @Test
    void testContactCreationSuccess() {

        Contact contact = new Contact("MM001", "Mickey", "Mouse", "4075551940", "1 Disney Castle Way");

        assertEquals("Mickey", contact.getFirstName());
        assertEquals("Mouse", contact.getLastName());
        assertEquals("4075551940", contact.getPhone());
        assertEquals("1 Disney Castle Way", contact.getAddress());
    }


    // Ensure that creating a contact with a null contact ID throws an exception
    @Test
    void testInvalidContactID() {

        assertThrows(IllegalArgumentException.class, () -> {
            new Contact(null, "Minnie", "Mouse", "3215552020", "2 Magic Kingdom Ln");
        });
    }


    // Ensure that creating a contact with a short phone number throws an exception
    @Test
    void testInvalidPhoneTooShort() {

        assertThrows(IllegalArgumentException.class, () -> {
            new Contact("MM002", "Donald", "Duck", "55512", "3 Toon Town Blvd");
        });
    }


    // Verify that setter methods properly update contact details
    @Test
    void testSettersWorkCorrectly() {

        Contact contact = new Contact("MM003", "Minnie", "Mouse", "3215552020", "2 Magic Kingdom Ln");

        contact.setFirstName("Daisy");
        contact.setLastName("Duck");
        contact.setPhone("5557778888");
        contact.setAddress("4 Dreamlight Path");

        assertEquals("Daisy", contact.getFirstName());
        assertEquals("Duck", contact.getLastName());
        assertEquals("5557778888", contact.getPhone());
        assertEquals("4 Dreamlight Path", contact.getAddress());
    }
}
