/**
 * Title: TaskServiceTest.java
 * Purpose: Unit tests for validating TaskService behavior including adding,
 * updating, and deleting Task objects while enforcing unique task IDs.
 * Created By: Tyler Hubbell
 * Last Updated: 11/17/2025
 */

import static org.junit.jupiter.api.Assertions.*;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

public class TaskServiceTest {

    private TaskService taskService;

    /**
     * Initializes a fresh TaskService instance before each test to ensure
     * test independence and a clean state.
     */

    @BeforeEach
    public void setUp() {
        taskService = new TaskService();
    }

    /**
     * Verifies that a task can be added successfully when using a unique ID.
     */

    @Test
    public void testAddTaskWithUniqueId() {
        taskService.addTask("1", "Task One", "First task");

        Task task = taskService.getTask("1");

        assertNotNull(task);
        assertEquals("Task One", task.getName());
        assertEquals("First task", task.getDescription());
    }

    /**
     * Ensures that attempting to add a task with a duplicate ID
     * results in an IllegalArgumentException.
     */

    @Test
    public void testAddTaskWithDuplicateIdThrowsException() {
        taskService.addTask("1", "Task One", "First task");

        assertThrows(IllegalArgumentException.class, () -> {
            taskService.addTask("1", "Duplicate", "Should fail");
        });
    }

    /**
     * Verifies that a task can be deleted by its ID and is no longer
     * retrievable from the service.
     */

    @Test
    public void testDeleteTaskById() {
        taskService.addTask("1", "Task One", "First task");

        taskService.deleteTask("1");

        assertNull(taskService.getTask("1"));
    }

    /**
     * Ensures that deleting a non-existing task ID results in an exception.
     */

    @Test
    public void testDeleteNonExistingTaskThrowsException() {
        assertThrows(IllegalArgumentException.class, () -> {
            taskService.deleteTask("999");
        });
    }

    /**
     * Verifies that the task name can be updated for an existing task ID.
     */

    @Test
    public void testUpdateTaskNameById() {
        taskService.addTask("1", "Old Name", "Desc");

        taskService.updateTaskName("1", "New Name");
        Task task = taskService.getTask("1");

        assertEquals("New Name", task.getName());
    }

    /**
     * Verifies that the task description can be updated for an existing task ID.
     */

    @Test
    public void testUpdateTaskDescriptionById() {
        taskService.addTask("1", "Name", "Old Desc");

        taskService.updateTaskDescription("1", "New Desc");
        Task task = taskService.getTask("1");

        assertEquals("New Desc", task.getDescription());
    }

    /**
     * Ensures that updating the name of a non-existing task ID
     * results in an exception.
     */

    @Test
    public void testUpdateNonExistingTaskNameThrowsException() {
        assertThrows(IllegalArgumentException.class, () -> {
            taskService.updateTaskName("999", "New Name");
        });
    }

    /**
     * Ensures that updating the description of a non-existing task ID
     * results in an exception.
     */

    @Test
    public void testUpdateNonExistingTaskDescriptionThrowsException() {
        assertThrows(IllegalArgumentException.class, () -> {
            taskService.updateTaskDescription("999", "New Desc");
        });
    }
}
