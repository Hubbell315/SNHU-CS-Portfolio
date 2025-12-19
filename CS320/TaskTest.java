/**
 * Title: TaskTest.java
 * Purpose: Unit tests for validating the Task class, ensuring proper enforcement
 * of field constraints, construction rules, and update functionality.
 * Created By: Tyler Hubbell
 * Last Updated: 11/17/2025
 */

import static org.junit.jupiter.api.Assertions.*;
import org.junit.jupiter.api.Test;

public class TaskTest {

    /**
     * Verifies that a Task object is successfully created with valid parameters.
     */

    @Test
    public void testTaskCreationValid() {
        Task task = new Task("12345", "Test Name", "This is a test description.");

        assertEquals("12345", task.getTaskId());
        assertEquals("Test Name", task.getName());
        assertEquals("This is a test description.", task.getDescription());
    }

    /**
     * Ensures that a null task ID triggers validation failure.
     */

    @Test
    public void testTaskIdCannotBeNull() {
        assertThrows(IllegalArgumentException.class, () -> {
            new Task(null, "Name", "Desc");
        });
    }

    /**
     * Ensures that a task ID exceeding the 10-character limit throws an exception.
     */

    @Test
    public void testTaskIdTooLongThrowsException() {
        assertThrows(IllegalArgumentException.class, () -> {
            new Task("12345678901", "Name", "Desc"); // 11 characters
        });
    }

    /**
     * Ensures that a null name triggers validation failure.
     */

    @Test
    public void testNameCannotBeNull() {
        assertThrows(IllegalArgumentException.class, () -> {
            new Task("123", null, "Desc");
        });
    }

    /**
     * Ensures that a name exceeding the 20-character limit throws an exception.
     */

    @Test
    public void testNameTooLongThrowsException() {
        String longName = "This name is longer than 20";
        assertThrows(IllegalArgumentException.class, () -> {
            new Task("123", longName, "Desc");
        });
    }

    /**
     * Ensures that a null description triggers validation failure.
     */

    @Test
    public void testDescriptionCannotBeNull() {
        assertThrows(IllegalArgumentException.class, () -> {
            new Task("123", "Name", null);
        });
    }

    /**
     * Ensures that a description exceeding the 50-character limit throws an exception.
     */

    @Test
    public void testDescriptionTooLongThrowsException() {
        String longDesc = "This description is definitely longer than fifty characters in length.";
        assertThrows(IllegalArgumentException.class, () -> {
            new Task("123", "Name", longDesc);
        });
    }

    /**
     * Validates that the task name can be successfully updated.
     */

    @Test
    public void testUpdateNameValid() {
        Task task = new Task("123", "Old Name", "Desc");

        task.setName("New Name");

        assertEquals("New Name", task.getName());
    }

    /**
     * Validates that the task description can be successfully updated.
     */

    @Test
    public void testUpdateDescriptionValid() {
        Task task = new Task("123", "Name", "Old description");

        task.setDescription("New description");

        assertEquals("New description", task.getDescription());
    }
}
