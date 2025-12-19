/**
 * Title: Appointment.java
 *
 * Purpose: Defines the Appointment object used within the mobile application
 * Enforces strict validation rules for appointment ID, date, and description
 * The appointment ID is immutable, while the date and description fields
 * remain read-only
 *
 * Key Responsibilities:
 * Store appointment information safely
 * Enforce validation for all required attributes
 * Prevent creation of invalid Appointment objects
 *
 * Created By: Tyler Hubbell
 * Last Updated: 11/24/2025
 */

import java.util.Date;

public class Appointment {


    // Immutable Appointment ID
    private final String appointmentId;

    // Appointment Fields
    // Date must not be null or in the past
    // Can add in no appointments allowed to be created less than 1 hour in advance for future
    private Date appointmentDate;
    private String description;

    /**
     * Constructor initializes the Appointment object and enforces
     * all validation rules required by the specification.
     *
     * @param appointmentId   Unique ID for the appointment, required - max 10 characters
     * @param appointmentDate Date of the appointment, required - cannot be in the past
     * @param description     Appointment description, required - max 50 characters
     */
    public Appointment(String appointmentId, Date appointmentDate, String description) {

        // Appointment ID Validation
        if (appointmentId == null || appointmentId.length() > 10) {
            throw new IllegalArgumentException("Invalid appointment ID");
        }

        // Appointment Date Validation
        if (appointmentDate == null || appointmentDate.before(new Date())) {
            throw new IllegalArgumentException("Invalid appointment date");
        }

        // Description Validation
        if (description == null || description.length() > 50) {
            throw new IllegalArgumentException("Invalid appointment description");
        }

        this.appointmentId = appointmentId;
        this.appointmentDate = appointmentDate;
        this.description = description;
    }

    // Getters
    // Appointment ID is immutable, others read-only
    public String getAppointmentId() {
        return appointmentId;
    }

    public Date getAppointmentDate() {
        return appointmentDate;
    }

    public String getDescription() {
        return description;
    }
}
