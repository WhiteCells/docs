Access Controls

- `//encore:api public`
- `//encore:api private`
- `//encore:api auth`

define api

```go
func Api(ctx context.Context, p *Params) (*Response, error)

func Api(ctx context.Context) (*Response, error)

func Api(ctx context.Context, p *Prarms) error

func Api(ctx context.Context) error
```

