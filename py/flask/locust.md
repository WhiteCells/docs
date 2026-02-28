```sh
pip install locust
```



```python
from locust import HttpUser, task, between

class ApiUser(HttpUser):
    wait_time = between(1, 2)

    @task
    def xxx_api_test(self):
        self.client.get("/")
```



```sh
locust -f <locustfile>.py
```

