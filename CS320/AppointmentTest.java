/**
 * Title: AppointmentTest.java
 * Purpose: Validates all functionality in the Appointment class
 * Ensures constructor validation behaves as expected
 *
 * Key Responsibilities:
 * Verify valid appointment creation
 * Verify ID, date, and description validation rules
 *
 * Created By: Tyler Hubbell
 * Last Updated: 11/24/2025
 */

import static org.junit.jupiter.api.Assertions.*;
import java.util.Date;
import org.junit.jupiter.api.Test;

public class AppointmentTest {

    @Test
    public void testValidAppointmentCreation() {
        Date future = new Date(System.currentTimeMillis() + 3600000);
        Appointment a = new Appointment("12345", future, "Test description");

        assertEquals("12345", a.getAppointmentId());
        assertEquals(future, a.getAppointmentDate());
        assertEquals("Test description", a.getDescription());
    }

    @Test
    public void testAppointmentIdNull() {
        Date future = new Date(System.currentTimeMillis() + 3600000);
        assertThrows(IllegalArgumentException.class, () -> {
            new Appointment(null, future, "Valid");
        });
    }

    @Test
    public void testAppointmentIdTooLong() {
        Date future = new Date(System.currentTimeMillis() + 3600000);
        assertThrows(IllegalArgumentException.class, () -> {
            new Appointment("12345678901", future, "Valid");
        });
    }

    @Test
    public void testAppointmentDateNull() {
        assertThrows(IllegalArgumentException.class, () -> {
            new Appointment("123", null, "Valid");
        });
    }

    @Test
    public void testAppointmentDatePast() {
        Date past = new Date(System.currentTimeMillis() - 3600000);
        assertThrows(IllegalArgumentException.class, () -> {
            new Appointment("123", past, "Valid");
        });
    }

    @Test
    public void testDescriptionNull() {
        Date future = new Date(System.currentTimeMillis() + 3600000);
        assertThrows(IllegalArgumentException.class, () -> {
            new Appointment("123", future, null);
        });
    }

    @Test
    public void testDescriptionTooLong() {
        Date future = new Date(System.currentTimeMillis() + 3600000);
        String longDesc = "A".repeat(51);

        assertThrows(IllegalArgumentException.class, () -> {
            new Appointment("123", future, longDesc);
        });
    }
}
