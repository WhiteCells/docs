```sh
pip install alembic
alembic init alembic
```

修改

```python
from app.config import Config

# this is the Alembic Config object, which provides
# access to the values within the .ini file in use.
config = context.config
config.set_main_option('sqlalchemy.url', Config.SYNC_DATABASE_URL())

# ...
# add your model's MetaData object here
# for 'autogenerate' support
# from myapp import mymodel
# target_metadata = mymodel.Base.metadata
from app.utils.database.base import Base
target_metadata = Base.metadata
```

