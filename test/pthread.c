#include <stdio.h>
#include <pthread.h>

int main(void)
{
    pthread_rwlock_t  m_rw_lock;
    pthread_rwlock_init(&m_rw_lock, NULL);

    pthread_rwlock_rdlock(&m_rw_lock);
    printf("lock once\n");

    pthread_rwlock_wrlock(&m_rw_lock);

    printf("lock twice\n");

    pthread_rwlock_unlock(&m_rw_lock);
    printf("unlock once\n");

    pthread_rwlock_unlock(&m_rw_lock);
    printf("unlock twice\n");

    return 0;
}
