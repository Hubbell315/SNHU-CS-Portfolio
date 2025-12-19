/**
 * Title: Task.java
 * Purpose: Defines the Task object with validation for all required fields and
 * provides controlled update functionality for editable properties.
 * Created By: Tyler Hubbell
 * Last Updated: 11/17/2025
 */

public class Task {

    // Immutable task ID (cannot be updated after object creation)
    private final String taskId;

    // Editable fields
    private String name;
    private String description;

    /**
     * Constructor initializes the Task object and enforces all validation rules.
     *
     * @param taskId      Unique ID for the task (required, max 10 characters)
     * @param name        Name of the task (required, max 20 characters)
     * @param description Description of the task (required, max 50 characters)
     */

    public Task(String taskId, String name, String description) {

        // Task ID validation
        if (taskId == null || taskId.length() > 10) {
            throw new IllegalArgumentException("Invalid task ID");
        }

        // Name validation
        if (name == null || name.length() > 20) {
            throw new IllegalArgumentException("Invalid task name");
        }

        // Description validation
        if (description == null || description.length() > 50) {
            throw new IllegalArgumentException("Invalid task description");
        }

        this.taskId = taskId;
        this.name = name;
        this.description = description;
    }

    // Getters, Task ID is read-only

    public String getTaskId() {
        return taskId;
    }

    public String getName() {
        return name;
    }

    public String getDescription() {
        return description;
    }

    // Updatable Fields with Validation

    /**
     * Updates the task name while enforcing validation rules.
     *
     * @param name New task name (required, max 20 characters)
     */

    public void setName(String name) {
        if (name == null || name.length() > 20) {
            throw new IllegalArgumentException("Invalid task name");
        }
        this.name = name;
    }

    /**
     * Updates the task description while enforcing validation rules.
     *
     * @param description New task description (required, max 50 characters)
     */

    public void setDescription(String description) {
        if (description == null || description.length() > 50) {
            throw new IllegalArgumentException("Invalid task description");
        }
        this.description = description;
    }
}
