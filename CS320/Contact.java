/**
 * Title: Contact.java
 * Purpose: Defines the Contact object with validation for all fields and provides
 * update functionality
 * Created By: Tyler Hubbell
 * Last Updated: 11/11/2025
 */

public class Contact {

    private final String contactID;
    private String firstName;
    private String lastName;
    private String phone;
    private String address;


    // Constructor initializes all fields and enforces validation rules
    public Contact(String contactID, String firstName, String lastName, String phone, String address) {

        // Contact ID validation
        if (contactID == null || contactID.length() > 10) {
            throw new IllegalArgumentException("Invalid contact ID");
        }

        // First name validation
        if (firstName == null || firstName.length() > 10) {
            throw new IllegalArgumentException("Invalid first name");
        }

        // Last name validation
        if (lastName == null || lastName.length() > 10) {
            throw new IllegalArgumentException("Invalid last name");
        }

        // Phone validation
        if (phone == null || phone.length() != 10 || !phone.matches("\\d+")) {
            throw new IllegalArgumentException("Invalid phone number");
        }

        // Address validation
        if (address == null || address.length() > 30) {
            throw new IllegalArgumentException("Invalid address");
        }

        this.contactID = contactID;
        this.firstName = firstName;
        this.lastName = lastName;
        this.phone = phone;
        this.address = address;
    }


    // Getters return each contact field
    public String getContactID() {
        return contactID;
    }

    public String getFirstName() {
        return firstName;
    }

    public String getLastName() {
        return lastName;
    }

    public String getPhone() {
        return phone;
    }

    public String getAddress() {
        return address;
    }


    // Setters update mutable fields with validation
    public void setFirstName(String firstName) {

        if (firstName == null || firstName.length() > 10)
            throw new IllegalArgumentException("Invalid first name");

        this.firstName = firstName;
    }

    public void setLastName(String lastName) {

        if (lastName == null || lastName.length() > 10)
            throw new IllegalArgumentException("Invalid last name");

        this.lastName = lastName;
    }

    public void setPhone(String phone) {

        if (phone == null || phone.length() != 10 || !phone.matches("\\d+"))
            throw new IllegalArgumentException("Invalid phone number");

        this.phone = phone;
    }

    public void setAddress(String address) {

        if (address == null || address.length() > 30)
            throw new IllegalArgumentException("Invalid address");

        this.address = address;
    }
}
