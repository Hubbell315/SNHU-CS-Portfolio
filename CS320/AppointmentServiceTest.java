/**
 * Title: AppointmentServiceTest.java
 * Purpose: Validates the AppointmentService class functionality
 * Ensures adding and deleting appointments works correctly
 *
 * Key Responsibilities:
 * Verify unique ID enforcement
 * Verify deletion behavior
 *
 * Created By: Tyler Hubbell
 * Last Updated: 11/24/2025
 */

import static org.junit.jupiter.api.Assertions.*;
import java.util.Date;
import org.junit.jupiter.api.Test;

public class AppointmentServiceTest {

    @Test
    public void testAddAppointmentValid() {
        AppointmentService service = new AppointmentService();
        Date future = new Date(System.currentTimeMillis() + 3600000);

        // Appointment ID and description
        Appointment appt = new Appointment("APT001", future, "Primary care doctor visit");

        service.addAppointment(appt);

        // Verify the appointment was added successfully
        assertEquals(appt, service.getAppointment("APT001"));
    }

    @Test
    public void testAddDuplicateAppointmentId() {
        AppointmentService service = new AppointmentService();
        Date future = new Date(System.currentTimeMillis() + 3600000);

        // Same ID to test duplication enforcement
        Appointment first = new Appointment("VISIT12", future, "Follow-up consultation");
        Appointment duplicate = new Appointment("VISIT12", future, "Another appointment");

        service.addAppointment(first);

        // Adding duplicated ID should throw exception
        assertThrows(IllegalArgumentException.class, () -> {
            service.addAppointment(duplicate);
        });
    }

    @Test
    public void testDeleteAppointmentValid() {
        AppointmentService service = new AppointmentService();
        Date future = new Date(System.currentTimeMillis() + 3600000);

        // Valid appointment to be deleted
        Appointment appt = new Appointment("CHECKUP9", future, "General wellness check");

        service.addAppointment(appt);

        // Delete appointment and verify it's removed
        service.deleteAppointment("CHECKUP9");
        assertNull(service.getAppointment("CHECKUP9"));
    }

    @Test
    public void testDeleteAppointmentNotFound() {
        AppointmentService service = new AppointmentService();

        // Attempting to delete non-existent appointment should throw exception
        assertThrows(IllegalArgumentException.class, () -> {
            service.deleteAppointment("NO_SUCH_ID");
        });
    }
}


