/**
 * Title: AppointmentService.java
 * Purpose: Manages Appointment objects within the application
 * Supports adding and deleting appointments while enforcing unique IDs
 *
 * Key Responsibilities:
 * Store appointments safely using in-memory data structures
 * Ensure no duplicate appointment IDs are added
 * Allow deletion of appointments by ID
 *
 * Created By: Tyler Hubbell
 * Last Updated: 11/24/2025
 */

import java.util.HashMap;
import java.util.Map;

public class AppointmentService {

    // Map of appointment ID to Appointment object
    private final Map<String, Appointment> appointmentMap = new HashMap<>();

    /**
     * Adds a new appointment to the service
     * Appointment IDs must be unique
     *
     * @param appointment the Appointment object to add
     */
    public void addAppointment(Appointment appointment) {

        if (appointmentMap.containsKey(appointment.getAppointmentId())) {
            throw new IllegalArgumentException("Appointment ID already exists");
        }

        appointmentMap.put(appointment.getAppointmentId(), appointment);
    }

    /**
     * Deletes an appointment by ID
     *
     * @param appointmentId the unique ID of the appointment to delete
     */
    public void deleteAppointment(String appointmentId) {

        if (!appointmentMap.containsKey(appointmentId)) {
            throw new IllegalArgumentException("Appointment ID not found");
        }

        appointmentMap.remove(appointmentId);
    }

    /**
     * Returns an appointment by ID
     * Used for verification in tests
     *
     * @param appointmentId ID of the appointment to retrieve
     * @return the Appointment object or null if not found
     */
    public Appointment getAppointment(String appointmentId) {
        return appointmentMap.get(appointmentId);
    }
}
